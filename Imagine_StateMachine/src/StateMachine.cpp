#include "Imagine_StateMachine/StateMachine.h"

#include "Imagine_StateMachine/StateMachineState.h"
#include "Imagine_StateMachine/common_definition.h"

namespace Imagine_Tool
{

namespace Imagine_StateMachine
{

StateMachine::StateMachine() : root_state_(nullptr)
{
}

StateMachine::~StateMachine()
{
}

StateMachine* StateMachine::RegisterState(StateMachineState* state)
{
    root_state_ = state;
    std::queue<StateMachineState*> state_queue;
    state_queue.push(state);
    while (state_queue.size()) {
        StateMachineState* temp_state = state_queue.front();
        temp_state->sm_ = this;
        state_map_.insert(std::make_pair(temp_state->GetStateName(), temp_state));
        printf("%s\n", temp_state->GetStateName().c_str());
        for (auto it = temp_state->subState_map_.begin(); it != temp_state->subState_map_.end(); it++) {
            state_queue.push(it->second);
        }
        state_queue.pop();
    }
    
    return this;
}

StateMachine* StateMachine::ActiveRootState() const
{
    root_state_->Enter();

    return this;
}

StateMachine* StateMachine::EventExecute(const StateMachineEvent& evt)
{
    std::priority_queue<std::pair<StandardizedCallback, TransitionEventPriority>, std::vector<std::pair<StandardizedCallback, TransitionEventPriority>>, PriorityCmp<StandardizedCallback, TransitionEventPriority>> trans_evt_cbs;
    std::priority_queue<std::pair<StandardizedCallback, ActorEventPriority>, std::vector<std::pair<StandardizedCallback, ActorEventPriority>>, PriorityCmp<StandardizedCallback, ActorEventPriority>> actor_evt_cbs;
    for (auto active_state_it = active_state_.begin(); active_state_it != active_state_.end(); active_state_it++) {
        if (active_state_it->second->trans_evt_cbs_.find(evt) != active_state_it->second->trans_evt_cbs_.end()) {
            trans_evt_cbs.push(active_state_it->second->trans_evt_cbs_.find(evt)->second);
        }
        if (active_state_it->second->actor_evt_cbs_.find(evt) != active_state_it->second->actor_evt_cbs_.end()) {
            actor_evt_cbs.push(active_state_it->second->actor_evt_cbs_.find(evt)->second);
        }
    }

    while (trans_evt_cbs.size()) {
        if (trans_evt_cbs.top().first()) {
            return this;
        }
        trans_evt_cbs.pop();
    }

    while (actor_evt_cbs.size()) {
        if (actor_evt_cbs.top().first()) {
            return this;
        }
        actor_evt_cbs.pop();
    }

    return this;
}

StateMachine* StateMachine::ConditionExecute()
{
    while (true) {
        std::priority_queue<std::pair<StandardizedCallback, TransitionConditionPriority>, std::vector<std::pair<StandardizedCallback, TransitionConditionPriority>>, PriorityCmp<StandardizedCallback, TransitionConditionPriority>> trans_cond_cbs;
        for (auto active_state_it = active_state_.begin(); active_state_it != active_state_.end(); active_state_it++) {
            for (auto cb_it = active_state_it->second->trans_cond_cbs_.begin(); cb_it != active_state_it->second->trans_cond_cbs_.end(); cb_it++) {
                trans_cond_cbs.push(cb_it->second);
            }
        }
        while (trans_cond_cbs.size()) {
            if (trans_cond_cbs.top().first()) {
                break;
            }
            trans_cond_cbs.pop();
        }
    }

    std::priority_queue<std::pair<StandardizedCallback, ActorConditionPriority>, std::vector<std::pair<StandardizedCallback, ActorConditionPriority>>, PriorityCmp<StandardizedCallback, ActorConditionPriority>> actor_cond_cbs;
    for (auto active_state_it = active_state_.begin(); active_state_it != active_state_.end(); active_state_it++) {
        for (auto cb_it = active_state_it->second->actor_cond_cbs_.begin(); cb_it != active_state_it->second->actor_cond_cbs_.end(); cb_it++) {
            actor_cond_cbs.push(cb_it->second);
        }
    }
    while (actor_cond_cbs.size()) {
        actor_cond_cbs.top().first();
        actor_cond_cbs.pop();
    }

    return this;
}

StateMachineState* StateMachine::GetRootState() const
{
    return root_state_;
}

StateMachine* StateMachine::AddActiveState(StateMachineState* active_state)
{
    active_state_.insert(std::make_pair(active_state->GetStateName(), active_state));

    return this;
}

StateMachine* StateMachine::RemoveActiveState(StateMachineState* active_state)
{
    if (active_state_.find(active_state->GetStateName()) == active_state_.end()) {
        throw std::exception();
    }
    active_state_.erase(active_state->GetStateName());

    return this;
}

StateMachineState* StateMachine::GetStatePtr(const std::string& state_name) const
{
    auto target_state_it = state_map_.find(state_name);
    if (target_state_it != state_map_.end()) {
        return target_state_it->second;
    }

    return nullptr;
}

} // namespace Imagine_StateMachine

} // namespace Imagine_Tool
