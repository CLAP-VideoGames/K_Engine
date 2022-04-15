#include "LogManager.h"

#include <iostream>

#include <utils_prj/checkML.h>

namespace K_Engine {
	std::unique_ptr<LogManager> LogManager::instance = nullptr;

	LogManager::LogManager() = default;

	LogManager::~LogManager() = default;

	bool LogManager::Init() {
		try {
			instance.reset(new LogManager());
		}
		catch (const std::exception&) {
			return false;
		}

		return true;
	}

	bool LogManager::Shutdown() {
		instance.reset();
		return true;
	}

	LogManager* LogManager::GetInstance() {
		return instance.get();
	}

	// Adds a log to the log registry
	void LogManager::addLog(std::string msg, logType ty) {
		log l; l.message = msg; l.type = ty;
		reg.push_back(l);
	}

	// Prints the type of the log and its message
	void LogManager::printLog() {
		for (log l : reg) {
			std::string type;
			switch (l.type)
			{
			case info:
				type = "INFO";
				break;
			case error:
				type = "ERROR";
				break;
			}
			std::cout << type << " - " << l.message << "\n";
		}

		// maybe we could create a txt file with the whole log
	}

	// Clears the log registry
	void LogManager::clearLog() {
		reg.clear();
	}
}