#ifndef IMAGINE_STATEMACHINE_COMMON_TYPENAME_H
#define IMAGINE_STATEMACHINE_COMMON_TYPENAME_H

#include <string>
#include <functional>

namespace Imagine_Tool
{

namespace Imagine_StateMachine
{

#define TRANSITION_TRUE_CONDITION [](StateMachineState* src, StateMachineState* tgt, StateMachineEvent evt) -> bool { return true; }
#define ACTOR_TRUE_CONDITION [](StateMachineState* src, StateMachineEvent evt) -> bool { return true; }

class StateMachineState;

using StateMachineEvent = std::string;          // event类型(默认为string)
using TransitionEventPriority = size_t;         // 事件触发式跳转处理器的优先级类型(事件触发)
using TransitionConditionPriority = size_t;     // 条件触发式跳转处理器的优先级类型(定时轮询)
using ActorEventPriority = size_t;              // 事件触发式状态处理器的优先级类型(事件触发)
using ActorConditionPriority = size_t;          // 条件触发式状态处理器的优先级类型(定时轮询)

using TransitionConditionCheckCallback = std::function<bool(StateMachineState*, StateMachineState*, StateMachineEvent)>;    // 跳转处理器触发条件函数
using ActorConditionCheckCallback = std::function<bool(StateMachineState*, StateMachineEvent)>;                             // 状态处理器触发条件函数
using TransitionEventCallback = std::function<bool(StateMachineState*, StateMachineState*, StateMachineEvent)>;             // 事件触发式跳转完成后的回调函数
using TransitionConditionCallback = std::function<bool(StateMachineState*, StateMachineState*, const std::string&)>;        // 条件触发式跳转完成后的回调函数
using ActorEventCallback = std::function<bool(StateMachineState*, StateMachineEvent)>;                                      // 事件触发式处理完成后的回调函数
using ActorConditionCallback = std::function<bool(StateMachineState*, const std::string&)>;                                 // 条件触发式处理完成后的回调函数

using StandardizedCallback = std::function<bool(void)>;                                                                     // SM最终保存的统一的函数

} // namespace Imagine_StateMachine

} // namespace Imagine_Tool


#endif