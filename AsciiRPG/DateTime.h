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

    int GetYear() const;
    int GetMonth() const;
    int GetDay() const;
    int GetHour() const;
    int GetMinute() const;
    int GetSeconds() const;
    string GetYearMonthDayString() const;
    string GetHourMinuteSecondString() const;

private:
    tm timeInfo;
};


#endif // !DATETIME_H
