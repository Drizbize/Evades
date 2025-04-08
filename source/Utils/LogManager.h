#pragma once

#include <fstream>
#include <vector>
#include <iostream>
#include <string>
#include <chrono>
#include <ctime>
#include <iomanip>

#include "Service.h"
#include "utils.h"

#define str(value) (std::to_string(value))

enum class LogLevel
{
    None = 0,
    Error = 1,
    Warning = 2,
    Info = 3,
    Debug = 4
};

class ILogDriver
{
public:
    virtual void log(LogLevel& lvl, const std::string& log) = 0;

    std::string currentDateTime();
    std::string getColorByLvl(LogLevel& lvl);
};

class ConsoleLogDriver : public ILogDriver
{
public:
    void log(LogLevel& lvl, const std::string& log) override
    {
        std::cout << getColorByLvl(lvl) << currentDateTime() << " " << log << "\033[0m" << std::endl;
    }
};

class FileLogDriver : public ILogDriver
{
public:
    FileLogDriver(const std::string& filename) : m_filename(filename) {}

    void log(LogLevel& lvl, const std::string& log) override
    {
        std::ofstream out(m_filename, std::ios::app);
        if (out.is_open())
        {
            out << currentDateTime() << " " << log << std::endl;
        }
    }

private:
    std::string m_filename;
};

class LogManager
{
public:
    LogManager(LogLevel lvl);
    ~LogManager();

    static void Debug(const std::string& msg);
    static void Warning(const std::string& msg);
    static void Info(const std::string& msg);
    static void Error(const std::string& msg);
    static LogLevel getLogLvl();

    void log(LogLevel lvl, std::string msg);
    void addDriver(ILogDriver* driver);

private:
    std::vector<ILogDriver*> m_drivers;
    LogLevel m_currentLoglvl;
};

class DebugTimer
{
public:
    DebugTimer(const std::string& locationName = "", utls::Timer* cooldownTimer = nullptr)
        : locationName(locationName), startTime(std::chrono::high_resolution_clock::now()), timer(cooldownTimer)
    {
    }

    ~DebugTimer()
    {
        if (!timer || (timer && timer->isEnded()))
        {
            std::chrono::duration<double> duration = std::chrono::high_resolution_clock::now() - startTime;
            LogManager::Debug("{" + locationName + "}: " + str(duration.count() * 1000) + " ms");
        }
    }

private:
    utls::Timer* timer;
    std::string locationName;
    std::chrono::time_point<std::chrono::high_resolution_clock> startTime;
};