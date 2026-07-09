#ifndef LOGGER_H
#define LOGGER_H

#include "SingletonMacro.h"
#include <string>
#include <iostream>
#include <fstream>
#include <list>

using namespace std;

class Logger
{
public:
    const string LOG_FILE_FORMAT = "log {0}.log";
    const int RECENTLY_LOGGED_COUNT = 10;

    SINGLETON_WITH_INIT_AND_RELEASE(Logger);

public:
    static void LogInfo(const string& message);
    static void LogWarning(const string& message);
    static void LogError(const string& message);

    void Init();
    void OnRelease();

    const list<string>& GetRecentLogs();

private:
    void OnLogInfo(const string& message);
    void OnLogWarning(const string& message);
    void OnLogError(const string& message);
    void AddToRecentLogs(const string& message);

private:
    ofstream logFileStream;
    list<string> recentLogs;
};
#endif