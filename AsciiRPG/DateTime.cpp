#include "DateTime.h"

DateTime DateTime::Now()
{
    auto now = chrono::system_clock::now();
    time_t now_c = chrono::system_clock::to_time_t(now);
    tm localTime;
    localtime_s(&localTime, &now_c);
    return DateTime(localTime.tm_year + 1900, localTime.tm_mon + 1, localTime.tm_mday,
        localTime.tm_hour, localTime.tm_min, localTime.tm_sec);
}

DateTime::DateTime()
    : timeInfo()
{}

DateTime::DateTime(int year, int month, int day, int hour, int minute, int second)
    : timeInfo()
{
    timeInfo.tm_year = year - 1900;
    timeInfo.tm_mon = month - 1;
    timeInfo.tm_mday = day;
    timeInfo.tm_hour = hour;
    timeInfo.tm_min = minute;
    timeInfo.tm_sec = second;
}

void DateTime::AddSeconds(int seconds)
{
    timeInfo.tm_sec += seconds;
}

int DateTime::GetYear() const
{
    return timeInfo.tm_year + 1900;
}

int DateTime::GetMonth() const
{
    return timeInfo.tm_mon + 1;
}

int DateTime::GetDay() const
{
    return timeInfo.tm_mday;
}

int DateTime::GetHour() const
{
    return timeInfo.tm_hour;
}

int DateTime::GetMinute() const
{
    return timeInfo.tm_min;
}

int DateTime::GetSeconds() const
{
    return timeInfo.tm_sec;
}

string DateTime::GetYearMonthDayString() const
{
    return format("{}{}{}", GetYear(), GetMonth(), GetDay());
}

string DateTime::GetHourMinuteSecondString() const
{
    return format("{:02d}:{:02d}:{:02d}", GetHour(), GetMinute(), GetSeconds());
}

bool DateTime::operator==(const DateTime& other) const
{
    return std::mktime(const_cast<tm*>(&timeInfo)) < std::mktime(const_cast<tm*>(&other.timeInfo));
}

bool DateTime::operator<(const DateTime& other) const
{
    return std::mktime(const_cast<tm*>(&timeInfo)) < std::mktime(const_cast<tm*>(&other.timeInfo));
}

bool DateTime::operator>(const DateTime& other) const
{
    return std::mktime(const_cast<tm*>(&timeInfo)) > std::mktime(const_cast<tm*>(&other.timeInfo));
}

bool DateTime::operator<=(const DateTime& other) const
{
    return std::mktime(const_cast<tm*>(&timeInfo)) <= std::mktime(const_cast<tm*>(&other.timeInfo));
}

bool DateTime::operator>=(const DateTime& other) const
{
    return std::mktime(const_cast<tm*>(&timeInfo)) >= std::mktime(const_cast<tm*>(&other.timeInfo));
}
