#ifndef IMAGINE_STATEMACHINE_STATEMACHINE_H
#define IMAGINE_STATEMACHINE_STATEMACHINE_H

#include "common_typename.h"

#include <unordered_map>
#include <queue>
#include <vector>

namespace Imagine_Tool
{

namespace Imagine_StateMachine
{

class StateMachineState;

class StateMachine
{
 public:
    StateMachine();

    ~StateMachine();

    StateMachine* RegisterState(StateMachineState* state);

    StateMachine* EventExecute(const StateMachineEvent& evt);

    StateMachine* ConditionExecute();

    StateMachineState* GetRootState() const;

    StateMachine* AddActiveState(StateMachineState* active_state);

    StateMachine* RemoveActiveState(StateMachineState* active_state);

    StateMachineState* GetStatePtr(const std::string& state_name) const;

 private:
    StateMachineState* root_state_;
    std::unordered_map<std::string, StateMachineState*> state_map_;
    std::unordered_map<std::string, StateMachineState*> active_state_;
};

} // namespace Imagine_StateMachine

} // namespace Imagine_Tool

#endif