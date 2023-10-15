#ifndef IMAGINE_TOOL_TIMEUTIL_H
#define IMAGINE_TOOL_TIMEUTIL_H

#include <functional>
#include <sys/uio.h>
#include <time.h>

#include "common_definition.h"

namespace Imagine_Tool
{

class TimeStamp;
class Timer;

class TimeUtil
{
 public:
   static int CreateTimer();

   static bool ReadTimerfd(int timer_fd);

   static long long GetTimerfdSettingTime(int timer_fd);

   static struct timespec GetTimespecFromNow(const TimeStamp &time);

   static void SetDefaultTimerfd(const int timer_fd);

   static void ResetTimerfd(const int timer_fd, const TimeStamp &time);

   // 精度为微秒
   static long long GetNow();

   static long long MicroSecondsAddSeconds(long long time, double interval);

   static std::string ToDate(long long ms);

   static bool IsLeapYear(long long year);

 public:
   class TimerPtrCmp
   {
   public:
      bool operator()(const Timer *a, const Timer *b);
   };
};

} // namespace Imagine_Tool

#endif