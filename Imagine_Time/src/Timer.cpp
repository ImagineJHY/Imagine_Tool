#include "Imagine_Time/Timer.h"

#include "Imagine_Time/TimeStamp.h"
#include "Imagine_Time/TimeUtil.h"

namespace Imagine_Tool
{

namespace Imagine_Time
{

long long Timer::id_ = 0;
std::mutex Timer::lock_;

Timer::Timer(const TimeStamp &call_time, const TimerCallback &timer_callback, double interval)
    : call_time_(new TimeStamp(call_time)), timer_callback_(timer_callback), interval_(interval), repeat_(interval > 0.0), alive_(true) 
{
    std::unique_lock<std::mutex> lock(Timer::lock_);
    Timer::id_++;
    timer_id_ = Timer::id_;
}

Timer::~Timer()
{
    delete call_time_;
}

const Timer* Timer::RunCallback() const
{
    if (timer_callback_ != nullptr)timer_callback_();

    return this;
}

bool Timer::ResetCallTime()
{
    if (!alive_.load()) {
        return false;
    }

    if (repeat_) {
        call_time_->SetTime(TimeUtil::MicroSecondsAddSeconds(TimeUtil::GetNow(), interval_));
    } else {
        return false;
    }

    return true;
}

TimeStamp Timer::GetCallTime() const 
{
    return TimeStamp(call_time_->GetTime());
}

Timer* Timer::Close()
{
    alive_.store(false);

    return this;
}

long long Timer::GetTimerId() const
{
    return timer_id_;
}

bool Timer::IsAlive() const
{ 
    return alive_.load();
}
    
} // namespace Imagine_Time
    
} // namespace Imagine_Tool
