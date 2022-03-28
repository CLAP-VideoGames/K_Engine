#pragma once
#ifndef LOGMANAGER_H
#define LOGMANAGER_H

#include <string>
#include <memory>
#include <vector>


namespace K_Engine {
	class LogManager {
	public:
		enum logType { info, error };

		LogManager();
		~LogManager();

		static LogManager* GetInstance();

		static bool Init();
		static bool Shutdown();

		void addLog(std::string msg, logType ty);

		void printLog();

		void clearLog();

	private:
		static std::unique_ptr<LogManager> instance;

		struct log {
			std::string message;
			logType type;
		};

		std::vector<log> reg;
	};
}

#endif
