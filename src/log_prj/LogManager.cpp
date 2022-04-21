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

			instance.get()->logFile.open("k_engine.log");
		}
		catch (const std::exception&) {
			return false;
		}

		return true;
	}

	bool LogManager::Shutdown() {
		instance.get()->logFile.close();
		instance.reset();
		return true;
	}

	LogManager* LogManager::GetInstance() {
		return instance.get();
	}

	// Adds a log to the log registry
	bool LogManager::addLog(LogType ty, std::string msg) {
		Log l; l.message = msg; l.type = ty;
		reg.push_back(l);

		return l.type != LogType::FATAL;
	}

	// Prints the type of the log and its message
	void LogManager::printLogBuffer() {
		for (Log l : reg) {
			std::string type;
			switch (l.type) {
			case LogType::INFO: type = "INFO"; break;
			case LogType::WARNING: type = "WARNING"; break;
			case LogType::FATAL: type = "ERROR"; break;
			}

			std::cerr << type << " -> " << l.message << "\n";
			logFile << type << " -> " << l.message << "\n";
		}
	}

	bool LogManager::printLog(LogType ty, std::string msg) {
		bool exec = addLog(ty, msg);
		printLogBuffer();
		clearLogBuffer();
		return exec;
	}

	// Clears the log registry
	void LogManager::clearLogBuffer() {
		reg.clear();
	}
}