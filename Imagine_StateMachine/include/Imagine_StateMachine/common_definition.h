#ifndef IMAGINE_STATEMACHINE_COMMON_DEFINITION_H
#define IMAGINE_STATEMACHINE_COMMON_DEFINITION_H

#include <vector>
#include <string>

namespace Imagine_Tool
{

namespace Imagine_StateMachine
{

enum class StateMachineStateType
{
    NornalState = 0,
    RegionState = 1
};

template <typename CallbackType, typename PriorityType>
class PriorityCmp
{
 public:
    bool operator()(const std::pair<CallbackType, PriorityType>& a, const std::pair<CallbackType, PriorityType>& b);
};

template <typename CallbackType, typename PriorityType>
bool PriorityCmp<CallbackType, PriorityType>::operator()(const std::pair<CallbackType, PriorityType>& a, const std::pair<CallbackType, PriorityType>& b)
{
    return a.second > b.second ? true : false;
}

} // namespace Imagine_StateMachine

} // namespace Imagine_Tool


#endif