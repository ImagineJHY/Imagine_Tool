#include "Imagine_StateMachine/StateMachineState.h"

#include "Imagine_StateMachine/common_definition.h"
#include "Imagine_StateMachine/StateMachine.h"

namespace Imagine_Tool
{

namespace Imagine_StateMachine
{

StateMachineState::StateMachineState(const std::string& state_name, StateMachine* sm) : sm_(sm), state_name_(state_name), state_type_(StateMachineStateType::NornalState), parent_state_(nullptr), active_(false), default_subState_(nullptr)
{
}

StateMachineState::StateMachineState(const std::string& state_name, StateMachineState* const parent_state, StateMachine* sm, StateMachineStateType state_type) : sm_(sm), state_name_(state_name), state_type_(state_type), parent_state_(parent_state), active_(false), default_subState_(nullptr)
{
}

StateMachineState::~StateMachineState()
{
}

StateMachineState* StateMachineState::AddSubState(StateMachineState* subState)
{
    subState_map_.insert(std::make_pair(subState->GetStateName(), subState));

    return this;
}

StateMachineState* StateMachineState::SetDefaultSubState(StateMachineState* subState)
{
    // TODO : 应检查子节点是否正交
    // if (state_type_ == StateMachineStateType::RegionState) {
    //     throw std::exception();
    // }
    default_subState_ = subState;
    if (subState_map_.find(subState->GetStateName()) == subState_map_.end()) {
        subState_map_.insert(std::make_pair(subState->GetStateName(), subState));
    }

    return this;
}

StateMachineState* StateMachineState::RegisterTransitionEventCallback(const StateMachineEvent& evt, TransitionEventPriority prio, TransitionConditionCheckCallback cond, StateMachineState* aim_state, TransitionEventCallback cb)
{
    trans_evt_cbs_.insert(std::make_pair(evt, std::make_pair(std::bind(
        [](StateMachineState* src, StateMachineState* tgt, StateMachineEvent evt, TransitionConditionCheckCallback cond, TransitionEventCallback cb) -> bool {
            if (!cond(src, tgt, evt)) {
                return false;
            }
            src->TransitionToState(tgt);
            if (cb != nullptr) {
                cb(src, tgt, evt);
            }

            return true;
        }, this, aim_state, evt, cond, cb), prio)));
    
    return this;
}

StateMachineState* StateMachineState::RegisterTransitionConditionCallback(const std::string& cond_name, TransitionConditionPriority prio, TransitionConditionCheckCallback cond, StateMachineState* aim_state, TransitionConditionCallback cb)
{
   trans_cond_cbs_.insert(std::make_pair(cond_name, std::make_pair(std::bind(
        [](StateMachineState* src, StateMachineState* tgt, const std::string& cond_name, TransitionConditionCheckCallback cond, TransitionConditionCallback cb) -> bool {
            if (!cond(src, tgt, cond_name)) {
                return false;
            }
            src->TransitionToState(tgt);
            if (cb != nullptr) {
                cb(src, tgt, cond_name);
            }

            return true;
        }, this, aim_state, cond_name, cond, cb), prio)));

   return this;
}

StateMachineState* StateMachineState::RegisterActorEventCallback(const StateMachineEvent& evt, ActorEventPriority prio, ActorConditionCheckCallback cond, ActorEventCallback cb)
{
    actor_evt_cbs_.insert(std::make_pair(evt, std::make_pair(std::bind(
        [](StateMachineState* src, StateMachineEvent evt, ActorConditionCheckCallback cond, ActorEventCallback cb) -> bool {
            if (!cond(src, evt)) {
                return false;
            }
            if (cb != nullptr) {
                cb(src, evt);
            }

            return true;
        }, this, evt, cond, cb), prio)));

    return this;
}

StateMachineState* StateMachineState::RegisterActorConditionCallback(const std::string& cond_name, ActorConditionPriority prio, ActorConditionCheckCallback cond, ActorConditionCallback cb)
{
    actor_cond_cbs_.insert(std::make_pair(cond_name, std::make_pair(std::bind(
        [](StateMachineState* src, const std::string& cond_name, ActorConditionCheckCallback cond, ActorEventCallback cb) -> bool {
            if (!cond(src, cond_name)) {
                return false;
            }
            if (cb != nullptr) {
                cb(src, cond_name);
            }

            return true;
        }, this, cond_name, cond, cb), prio)));

    return this;
}

const StateMachineState* StateMachineState::FindCommonAncestor(const StateMachineState* state) const
{
    std::unordered_map<std::string, const StateMachineState*> ancestor_map;
    const StateMachineState* ancestor_state = parent_state_;
    if (ancestor_state == nullptr) {
        return this;
    }

    while (true) {
        if (ancestor_state == nullptr) {
            break;
        }
        if (ancestor_state->GetStateName() != state->GetStateName()) {
            ancestor_map.insert(std::make_pair(ancestor_state->GetStateName(), ancestor_state));
            ancestor_state = ancestor_state->GetParentState();
        } else {
            return state;
        }
    }
    ancestor_map.insert(std::make_pair(state_name_, this));

    ancestor_state = state->GetParentState();
    while (true) {
        if (ancestor_map.find(ancestor_state->GetStateName()) != ancestor_map.end()) {
            return ancestor_state;
        } else {
            ancestor_state = ancestor_state->GetParentState();
        }
    }

    return nullptr;
}

StateMachineState* StateMachineState::TransitionToState(StateMachineState* new_state)
{
    // if (new_state->IsActive()) {
    //     return this; // 当目标状态为Active, 不做任何改变(是否要退出当前状态)
    // }

    const StateMachineState* common_ancestor_state = FindCommonAncestor(new_state);
    std::queue<StateMachineState*> state_queue;
    std::stack<StateMachineState*> state_stack;
    StateMachineState* parent_state = this;
    while (parent_state->GetStateName() != common_ancestor_state->GetStateName()) {
        state_queue.push(parent_state);
        parent_state = parent_state->GetParentState();
    }
    parent_state = new_state;
    while (parent_state->GetStateName() != common_ancestor_state->GetStateName()) {
        state_stack.push(parent_state);
        parent_state = parent_state->GetParentState();
    }
    ExitAllsubState(); // 针对当公共父节点为当前节点的特殊情况, 特殊处理
    while (state_queue.size()) {
        state_queue.front()->Exit();
        state_queue.pop();
    }
    while (state_stack.size()) {
        if (state_stack.top()->state_type_ == StateMachineStateType::NornalState && state_stack.top()->parent_state_ != nullptr) {
            for (auto it = state_stack.top()->parent_state_->subState_map_.begin(); it != state_stack.top()->parent_state_->subState_map_.end(); it++) {
                if (it->second->GetStateName() != state_stack.top()->GetStateName()) {
                    it->second->Exit(); // 对于非正交状态, 检查亲兄弟是否全部退出
                }
            }
        }
        state_stack.top()->Enter();
        state_stack.pop();
    }

    return this;
}

std::string StateMachineState::GetStateName() const
{
    return state_name_;
}

bool StateMachineState::IsActive() const
{
    return active_;
}

StateMachineState* StateMachineState::GetParentState() const
{
    return parent_state_;
}

StateMachineState* StateMachineState::Enter()
{
    if (active_) {
        return this;
    }
    active_ = true;
    sm_->AddActiveState(this);
    onEnter();
    if (default_subState_ != nullptr) {
        default_subState_->Enter();
    }

    return this;
}

StateMachineState* StateMachineState::Exit()
{
    if (!active_) {
        return this;
    }
    active_ = false;
    sm_->RemoveActiveState(this);
    if (state_type_ == StateMachineStateType::RegionState) {
        parent_state_->ExitAllsubState();
    }
    for (auto it = subState_map_.begin(); it != subState_map_.end(); it++) {
            it->second->Exit();
    }
    onExit();

    return this;
}

StateMachineState* StateMachineState::ExitAllsubState()
{
    for (auto it = subState_map_.begin(); it != subState_map_.end(); it++) {
        it->second->Exit();
    }

    return this;
}

StateMachineState* StateMachineState::GetSubStatePtr(const std::string& state_name)
{
    std::unordered_map<std::string, StateMachineState*>::iterator target_state_it = subState_map_.find(state_name);
    if (target_state_it != subState_map_.end()) {
        return target_state_it->second;
    }

    return nullptr;
}

} // namespace Imagine_StateMachine

} // namespace Imagine_Tool
