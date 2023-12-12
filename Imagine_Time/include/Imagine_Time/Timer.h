#ifndef IMAGINE_TOOL_TIMER_H
#define IMAGINE_TOOL_TIMER_H

#include "common_typename.h"

#include <mutex>
#include <functional>
#include <atomic>

namespace Imagine_Tool
{

namespace Imagine_Time
{

class TimeStamp;

class Timer
{
 public:
    Timer(const TimeStamp &call_time, const TimerCallback &timer_callback, double interval = 0);

    ~Timer();

    const Timer* RunCallback() const;

    bool ResetCallTime();

    TimeStamp GetCallTime() const;

    Timer* Close();

    long long GetTimerId() const;

    bool IsAlive() const;

 private:
    static long long id_;
    static std::mutex lock_;

 private:
    TimeStamp* call_time_;             // 记录绝对时间,微秒为单位
    TimerCallback timer_callback_;     // 回调函数
    const double interval_;            // 记录时间间隔,秒为单位
    bool repeat_;                      // 是否重复定时

    long long timer_id_;
    std::atomic<bool> alive_;
};

} // namespace Imagine_Time

} // namespace Imagine_Tool

#endif