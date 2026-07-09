#include "Logger.h"

#include <format>
#include <chrono>
#include "DateTime.h"

using namespace std;

SINGLETON_INITIALIZER(Logger);

void Logger::Init()
{
    // 현재 시간 가져오기
    DateTime now = DateTime::Now();
    // 년_월_일_시_분_초 형식으로 로그 파일 이름 생성
    string logFileName = std::format("log_{:04d}{:02d}{:02d}_{:02d}_{:02d}_{:02d}.log",
        now.GetYear(),
        now.GetMonth(),
        now.GetDay(),
        now.GetHour(),
        now.GetMinute(),
        now.GetSeconds()
    );

    // 로그 파일 열기
    logFileStream.open(logFileName, ios::out | ios::app);
}

void Logger::OnRelease()
{
    logFileStream.close();
}

const list<string>& Logger::GetRecentLogs()
{
    return recentLogs;
}


void Logger::OnLogInfo(const string& message)
{
    logFileStream << "[" 
        << DateTime::Now().GetHourMinuteSecondString() 
        << "] "
        << "[INFO] " 
        << message 
        << endl;

    AddToRecentLogs(message);
}

void Logger::OnLogWarning(const string & message)
{
    logFileStream << "[" 
        << DateTime::Now().GetHourMinuteSecondString() 
        << "] "
        << "[WARN] " 
        << message 
        << endl;

    AddToRecentLogs(message);   
}

void Logger::OnLogError(const string & message)
{
    logFileStream << "[" 
        << DateTime::Now().GetHourMinuteSecondString() 
        << "] "
        << "[ERRO] " 
        << message 
        << endl;

    AddToRecentLogs(message);
}

void Logger::AddToRecentLogs(const string& message)
{
    if (recentLogs.size() >= RECENTLY_LOGGED_COUNT)
    {
        recentLogs.pop_front();
    }

    recentLogs.push_back(message);
}

void Logger::LogInfo(const string& message)
{
    GetInstance().OnLogInfo(message);
}

void Logger::LogWarning(const string & message)
{
    GetInstance().OnLogWarning(message);
}

void Logger::LogError(const string & message)
{
    GetInstance().OnLogError(message);
}