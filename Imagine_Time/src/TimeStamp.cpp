#include "Imagine_Time/TimeStamp.h"

namespace Imagine_Tool {

namespace Imagine_Time {

TimeStamp::TimeStamp(long long time) : micro_seconds_time_(time)
{
}

TimeStamp::TimeStamp(const TimeStamp& time_stamp)
{
    micro_seconds_time_ = time_stamp.GetTime();
}

TimeStamp::~TimeStamp()
{
}

long long TimeStamp::TimeStamp::GetTime() const
{
    return micro_seconds_time_;
}

bool TimeStamp::SetTime(long long time)
{
    micro_seconds_time_ = time;

    return true;
}

} // namespace Imagine_Time

} // namespace Imagine_Tool
