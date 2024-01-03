#ifndef IMAGINE_STATEMACHINE_STATEMACHINESTATE_H
#define IMAGINE_STATEMACHINE_STATEMACHINESTATE_H

#include "common_typename.h"

#include <stack>
#include <string>
#include <unordered_map>

namespace Imagine_Tool
{

namespace Imagine_StateMachine
{

class StateMachine;
enum class StateMachineStateType;

class StateMachineState
{

friend class StateMachine;

 public:
    /**
     * @brief 创建根节点使用的构造函数
    */
    StateMachineState(const std::string& state_name);

    /**
     * @brief 创建子节点使用的构造函数
    */
    StateMachineState(const std::string& state_name, StateMachineState* const parent_state, StateMachineStateType state_type = StateMachineStateType::NornalState);
    
    virtual ~StateMachineState();

    StateMachineState* AddSubState(StateMachineState* subState);

    virtual StateMachineState* AddRegionSubState() = 0;

    StateMachineState* SetDefaultSubState(StateMachineState* subState);

    /**
     * @brief 注册事件式跳转函数
    */
    StateMachineState* RegisterTransitionEventCallback(const StateMachineEvent& evt, TransitionEventPriority prio, TransitionConditionCheckCallback cond, StateMachineState* aim_state, TransitionEventCallback cb);

    /**
     * @brief 注册条件式跳转函数
     * @param cond_name    条件的名字, 不起实际作用
     * @param priority     优先级
     * @param cond         条件
     * @param aim_state    目标状态
     * @param cb           回调函数
    */
    StateMachineState* RegisterTransitionConditionCallback(const std::string& cond_name, TransitionConditionPriority prio, TransitionConditionCheckCallback cond, StateMachineState* aim_state, TransitionConditionCallback cb);

    StateMachineState* RegisterActorEventCallback(const StateMachineEvent& evt, ActorEventPriority prio, ActorConditionCheckCallback cond, ActorEventCallback cb);

    StateMachineState* RegisterActorConditionCallback(const std::string& cond_name, ActorConditionPriority prio, ActorConditionCheckCallback cond, ActorConditionCallback cb);

    StateMachineState* TransitionToState(StateMachineState* new_state);

    std::string GetStateName() const;

    bool IsActive() const;

 private:
    virtual StateMachineState* onEnter() = 0;

    virtual StateMachineState* onExit() = 0;

    StateMachineState* Enter();

    StateMachineState* Exit();

    StateMachineState* ExitAllsubState();

    const StateMachineState* FindCommonAncestor(const StateMachineState* state) const;

    StateMachineState* GetParentState() const;

 private:
   const StateMachine* sm_;

 private:
    const std::string state_name_;
    const StateMachineStateType state_type_;
    StateMachineState* const parent_state_;
    bool active_;
    StateMachineState* default_subState_;
    std::unordered_map<std::string, StateMachineState*> subState_map_;
    std::unordered_map<StateMachineEvent, std::pair<StandardizedCallback, TransitionEventPriority>> trans_evt_cbs_;
    std::unordered_map<std::string, std::pair<StandardizedCallback, TransitionConditionPriority>> trans_cond_cbs_;
    std::unordered_map<StateMachineEvent, std::pair<StandardizedCallback, ActorEventPriority>> actor_evt_cbs_;
    std::unordered_map<std::string, std::pair<StandardizedCallback, ActorConditionPriority>> actor_cond_cbs_;
};

} // namespace Imagine_StateMachine

} // namespace Imagine_Tool

#endif