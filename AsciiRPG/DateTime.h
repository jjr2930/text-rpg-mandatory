#ifndef DATETIME_H
#define DATETIME_H

#include <string>
#include <chrono>

using namespace std;

class DateTime
{
public:
    static DateTime Now();
    
    DateTime();
    DateTime(int year, int month, int day, int hour, int minute, int second);

    void AddSeconds(int seconds);

    int GetYear() const;
    int GetMonth() const;
    int GetDay() const;
    int GetHour() const;
    int GetMinute() const;
    int GetSeconds() const;
    string GetYearMonthDayString() const;
    string GetHourMinuteSecondString() const;

    bool operator==(const DateTime& other) const;
    bool operator<(const DateTime& other) const;
    bool operator>(const DateTime& other) const;
    bool operator<=(const DateTime& other) const;
    bool operator>=(const DateTime& other) const;

private:
    tm timeInfo;
};


#endif // !DATETIME_H
