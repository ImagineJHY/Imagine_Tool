#include "Imagine_Time/Timer.h"

#include <sys/time.h>
#include <unistd.h>
#include <sys/timerfd.h>
#include <string.h>
#include <errno.h>

namespace Imagine_Tool
{

int TimeUtil::CreateTimer()
{
    int timer_fd = timerfd_create(CLOCK_MONOTONIC, TFD_NONBLOCK | TFD_CLOEXEC);
    if (timer_fd < 0) {
        throw std::exception();
    }

    return timer_fd;
}

bool TimeUtil::ReadTimerfd(int timer_fd)
{
    unsigned long long num;
    int ret = read(timer_fd, &num, sizeof(num));
    if (ret != sizeof(num)) {
        // printf("std::exception()::next time is %lld\n",TimeUtil::GetTimerfdSettingTime(timerfd_));
        // throw std::exception();
    }
    if (errno == EAGAIN) {
        // printf("......................%lld.....................\n",num);
        return false;
    }
    // printf("......................%d.....................\n",ret);
    // printf("there are %lld clocks occured!\n",num);
    return true;
}

long long TimeUtil::GetTimerfdSettingTime(int timer_fd)
{
    struct itimerspec set_time;
    timerfd_gettime(timer_fd, &set_time);

    return static_cast<long long>(set_time.it_value.tv_sec) * ms_per_second + static_cast<long long>(set_time.it_value.tv_nsec) / 1000;
}

struct timespec TimeUtil::GetTimespecFromNow(const TimeStamp &time)
{
    long long micro_seconds = time.GetTime() - GetNow();
    if (micro_seconds < 0) {
        printf("ur 2 small!\n");
    }
    // printf("micro seconds is %lld\n",micro_seconds);
    if (micro_seconds < 100) {
        micro_seconds = 100;
        printf("too short .....................................................................................too short\n");
    }
    struct timespec time_spec;
    // printf("Set seconds is %ld\n",new_value_.it_value.tv_sec*1000000+new_value_.it_value.tv_nsec*1000)
    time_spec.tv_sec = static_cast<time_t>(micro_seconds / ms_per_second);
    time_spec.tv_nsec = static_cast<long>((micro_seconds % ms_per_second) * 1000);

    return time_spec;
}

void TimeUtil::SetDefaultTimerfd(const int timer_fd)
{
    TimeStamp time(MicroSecondsAddSeconds(GetNow(), 5.0));
    struct itimerspec old_value;
    struct itimerspec new_value;
    memset(&old_value, 0, sizeof(old_value));
    memset(&new_value, 0, sizeof(new_value));
    new_value.it_value = GetTimespecFromNow(time);
    // memset(&new_value,0,sizeof(new_value));
    int ret = timerfd_settime(timer_fd, 0, &new_value, &old_value);
    if (ret) {
        printf("exception here3\n");
        throw std::exception();
    }
}

void TimeUtil::ResetTimerfd(const int timer_fd, const TimeStamp &time)
{
    struct itimerspec old_value;
    struct itimerspec new_value;
    memset(&old_value, 0, sizeof(old_value));
    memset(&new_value, 0, sizeof(new_value));
    new_value.it_value = GetTimespecFromNow(time);
    int ret = timerfd_settime(timer_fd, 0, &new_value, &old_value);
    // printf("reset timer after %lf\n",(new_value.it_value.tv_sec)+(new_value.it_value.tv_nsec/1000)*0.000001);
    if (ret) {
        printf("exception here1\n");
        throw std::exception();
    }
}

long long TimeUtil::GetNow()
{
    struct timeval tv;
    gettimeofday(&tv, NULL);

    return static_cast<long long>(tv.tv_sec) * ms_per_second + static_cast<long long>(tv.tv_usec);
}

long long TimeUtil::MicroSecondsAddSeconds(long long time, double interval)
{
    long long interval_us = static_cast<long long>(interval * ms_per_second);
    return static_cast<long long>(time + interval_us);
}

bool TimeUtil::TimerPtrCmp::operator()(const Timer *a, const Timer *b)
{
    return a->GetCallTime().GetTime() < b->GetCallTime().GetTime() ? true : false;
}

std::string TimeUtil::ToDate(long long ms)
{
    size_t year = GMT_FIRST_YEAR;
    size_t month;
    size_t day = 1;
    size_t hour = 0;
    size_t min = 0;
    size_t second = 0;
    bool is_leap_year = IsLeapYear(year);
    while((is_leap_year ? second_per_leap_year * ms_per_second : second_per_year * ms_per_second) <= ms) {
        year++;
        ms -= is_leap_year ? second_per_leap_year * ms_per_second : second_per_year * ms_per_second;
        is_leap_year = IsLeapYear(year);
    }

    if (is_leap_year) {
        for(month = static_cast<size_t>(MonthLeap::Jan); month != static_cast<size_t>(MonthLeap::Dec) + 1; month++) {
            long long temp_ms = day_per_month_leap.find(static_cast<MonthLeap>(month))->second * second_per_day * ms_per_second;
            if (temp_ms <= ms) {
                ms -= temp_ms;
            } else {
                month = month - static_cast<size_t>(MonthLeap::Jan) + 1;
                break;
            }
        }
    } else {
        for(month = static_cast<size_t>(Month::Jan); month != static_cast<size_t>(Month::Dec) + 1; month++) {
            long long temp_ms = day_per_month.find(static_cast<Month>(month))->second * second_per_day * ms_per_second;
            if (temp_ms <= ms) {
                ms -= temp_ms;
            } else {
                month = month - static_cast<size_t>(Month::Jan) + 1;
                break;
            }
        }
    }

    size_t day_ms = second_per_day * ms_per_second;
    while(day_ms <= ms) {
        ms -= day_ms;
        day++;
    }

    size_t hour_ms = second_per_hour * ms_per_second;
    while(hour_ms <= ms) {
        ms -= hour_ms;
        hour++;
    }

    size_t min_ms = second_per_min * ms_per_second;
    while(min_ms <= ms) {
        ms -= min_ms;
        min++;
    }

    while(ms_per_second <= ms) {
        ms -= ms_per_second;
        second++;
    }

    return std::to_string(year) + "-" + std::to_string(month) + "-" + std::to_string(day) + "." + std::to_string(hour) + ":" + std::to_string(min)+ ":" + std::to_string(second) + ":" + std::to_string(ms);
}

bool TimeUtil::IsLeapYear(long long year)
{
    return ((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0);
}

} // namespace Imagine_Tool