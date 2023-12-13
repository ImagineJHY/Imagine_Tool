#ifndef IMAGINE_TIME_COMMON_DEFINITION_h
#define IMAGINE_TIME_COMMON_DEFINITION_h

#include <unordered_map>

namespace Imagine_Tool
{

namespace Imagine_Time
{

#define GENERIC_DATE_SEPARATOR "-"
#define GENERIC_TIME_SEPARATOR ":"
#define SEPARATOR_OF_DATE_AND_TIME "."
#define SEPARATOR_OF_YEAR_AND_MONTH GENERIC_DATE_SEPARATOR
#define SEPARATOR_OF_MONTH_AND_DAY GENERIC_DATE_SEPARATOR
#define SEPARATOR_OF_HOUR_AND_MINUTE GENERIC_TIME_SEPARATOR
#define SEPARATOR_OF_MINUTE_AND_SECOND GENERIC_TIME_SEPARATOR
#define SEPARATOR_OF_SECOND_AND_MICROSECOND GENERIC_TIME_SEPARATOR

#define NOW_MS ::Imagine_Tool::Imagine_Time::TimeUtil::GetNow()

#define GMT_FIRST_YEAR 1970

#define DEFAULT_TIMER_INTERVAL 5.0

extern const long long ns_per_second;

extern const long long ms_per_second;

extern const long long second_per_min;

extern const long long second_per_hour;

extern const long long second_per_day;

extern const long long second_per_year;

extern const long long second_per_leap_year;

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

extern const std::unordered_map<Month, size_t> day_per_month;

extern const std::unordered_map<MonthLeap, size_t> day_per_month_leap;

} // namespace Imagine_Time

} // namespace Imagine_Tool

#endif