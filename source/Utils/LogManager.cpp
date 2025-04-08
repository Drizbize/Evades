#include "LogManager.h"

std::string ILogDriver::currentDateTime()
{
    auto now = std::chrono::system_clock::now();
    auto time = std::chrono::system_clock::to_time_t(now);
    std::tm* tmPtr = std::localtime(&time);

    char buffer[80];
    std::strftime(buffer, sizeof(buffer), "%Y-%d-%m %X", tmPtr);

    return buffer;
}

std::string ILogDriver::getColorByLvl(LogLevel& lvl)
{
    switch (lvl)
    {
    case LogLevel::Error:
        return "\033[31m"; // Red
    case LogLevel::Warning:
        return "\033[33m"; // Yellow
    case LogLevel::Info:
        return "\033[37m"; // White
    case LogLevel::Debug:
        return "\033[36m"; // Cyan
    default:
        return "\033[0m";  // Reset
    }
}

LogManager::LogManager(LogLevel lvl)
{
    m_currentLoglvl = lvl;
}

LogManager::~LogManager()
{
    for (ILogDriver* driver : m_drivers)
    {
        delete driver;
    }
}

void LogManager::Debug(const std::string& msg)
{
    Get<LogManager>().log(LogLevel::Debug, msg);
}

void LogManager::Warning(const std::string& msg)
{
    Get<LogManager>().log(LogLevel::Warning, msg);
}

void LogManager::Info(const std::string& msg)
{
    Get<LogManager>().log(LogLevel::Info, msg);
}

void LogManager::Error(const std::string& msg)
{
    Get<LogManager>().log(LogLevel::Error, msg);
}

LogLevel LogManager::getLogLvl()
{
    return Get<LogManager>().m_currentLoglvl;
}

void LogManager::log(LogLevel lvl, std::string msg)
{
    if (lvl > m_currentLoglvl)
    {
        return;
    }

    switch (lvl)
    {
    case LogLevel::None:
        return;
    case LogLevel::Error:
        msg = "[Error]: " + msg;
        break;
    case LogLevel::Warning:
        msg = "[Warning]: " + msg;
        break;
    case LogLevel::Info:
        msg = "[Info]: " + msg;
        break;
    case LogLevel::Debug:
        msg = "[Debug]: " + msg;
        break;
    }

    for (ILogDriver* driver : m_drivers)
    {
        driver->log(lvl, msg);
    }
}

void LogManager::addDriver(ILogDriver* driver)
{
    m_drivers.push_back(driver);
}
