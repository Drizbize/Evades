#include "LogManager.h"

std::string ILogDriver::currentDateTime()
{
	time_t now = time(0);
	struct tm tstruct;
	char buf[80];
	tstruct = *localtime(&now);

	strftime(buf, sizeof(buf), "%Y-%d-%m %X", &tstruct);

	return buf;
}

WORD ILogDriver::getColorByLvl(LogLevel& lvl)
{
	int ConsoleColorId = 7;

	switch (lvl)
	{
	case LogLevel::Error:
		ConsoleColorId = 12;
		break;
	case LogLevel::Warning:
		ConsoleColorId = 14;
		break;
	case LogLevel::Info:
		ConsoleColorId = 7;
		break;
	case LogLevel::Debug:
		ConsoleColorId = 11;
		break;
	default:
		break;
	}

	return (WORD)ConsoleColorId;
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
	default:
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