#pragma once
#ifndef LOGMANAGER_H
#define LOGMANAGER_H

#include <string>
#include <memory>
#include <vector>
#include <fstream>

namespace K_Engine {
	enum class LogType { INFO, WARNING, FATAL };

	class  __declspec(dllexport) LogManager {
	public:

		LogManager();
		~LogManager();

		static LogManager* GetInstance();

		static bool Init();
		static bool Shutdown();

		bool addLog(LogType ty, std::string msg);
		void printLogBuffer();
		bool printLog(LogType ty, std::string msg);

		void clearLogBuffer();

	private:
		static std::unique_ptr<LogManager> instance;

		struct Log {
			LogType type;
			std::string message;
		};

		std::vector<Log> reg;

		std::ofstream logFile;
	};
}

#endif
