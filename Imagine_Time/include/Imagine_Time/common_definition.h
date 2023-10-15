#ifndef IMAGINE_TOOL_TIME_COMMON_DEFINITION_h
#define IMAGINE_TOOL_TIME_COMMON_DEFINITION_h

#include <functional>
#include <unordered_map>

namespace Imagine_Tool
{

#define NOW_MS Imagine_Tool::TimeUtil::GetNow()

using TimerCallback = std::function<void()>;

#define GMT_FIRST_YEAR 1970

const long long ns_per_second = 1000 * 1000 * 1000;

const long long ms_per_second = 1000 * 1000;

const long long second_per_min = 60;

const long long second_per_hour = second_per_min * 60;

const long long second_per_day = second_per_hour * 24;

const long long second_per_year = second_per_day * 365;

const long long second_per_leap_year = second_per_day * 366;

enum class Month
{
    Jan = 1,
    Feb,
    Mar,
    Apr,
    May,
    Jun,
    Jul,
    Aug,
    Sept,
    Oct,
    Nov,
    Dec
};

enum class MonthLeap
{    
    Jan = 1,
    Feb,
    Mar,
    Apr,
    May,
    Jun,
    Jul,
    Aug,
    Sept,
    Oct,
    Nov,
    Dec
};

const std::unordered_map<Month, size_t> day_per_month{{Month::Jan, 31}, {Month::Feb, 28}, {Month::Mar, 31}, {Month::Apr, 30}, 
                                                      {Month::May, 31}, {Month::Jun, 30}, {Month::Jul, 31}, {Month::Aug, 31}, 
                                                      {Month::Sept, 30}, {Month::Oct, 31}, {Month::Nov, 30}, {Month::Dec, 31}};

const std::unordered_map<MonthLeap, size_t> day_per_month_leap{{MonthLeap::Jan, 31}, {MonthLeap::Feb, 29}, {MonthLeap::Mar, 31}, {MonthLeap::Apr, 30}, 
                                                               {MonthLeap::May, 31}, {MonthLeap::Jun, 30}, {MonthLeap::Jul, 31}, {MonthLeap::Aug, 31}, 
                                                               {MonthLeap::Sept, 30}, {MonthLeap::Oct, 31}, {MonthLeap::Nov, 30}, {MonthLeap::Dec, 31}};

} // namespace Imagine_Tool

#endif