#include "LogManager.h"

#include <iostream>

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

	void LogManager::addLog(std::string mess, logType ty) {
		log l; l.message = mess; l.type = ty;
		reg.push_back(l);
	}

	void LogManager::printLog() {
		for (log l : reg) {
			std::cout << l.type << " - " << l.message << "\n";
		}

		// it'd be cool to create a txt file with the whole log but my mister piskas pisko paskas told not to for the time being
	}

	void LogManager::clearLog() {
		reg.clear();
	}
}