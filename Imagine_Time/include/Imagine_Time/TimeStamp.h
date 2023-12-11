#ifndef IMAGINE_TOOL_TIMESTAMP_H
#define IMAGINE_TOOL_TIMESTAMP_H

namespace Imagine_Tool
{

namespace Imagine_Time
{

class TimeStamp
{
 public:
    explicit TimeStamp(long long time = 0);

    TimeStamp(const TimeStamp& time_stamp);

    ~TimeStamp();

    long long GetTime() const;

    bool SetTime(long long time);

 private:
    long long micro_seconds_time_;
};

} // namespace Imagine_Time

} // namespace Imagine_Tool

#endif