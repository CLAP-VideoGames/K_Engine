#pragma once
#ifndef LOGMANAGER_H
#define LOGMANAGER_H

#include <string>
#include <memory>

class LogManager {
public:
	LogManager();
	~LogManager();

	static LogManager* GetInstance();

	static bool Init(std::string n);
	static bool Shutdown();
private:
	static std::unique_ptr<LogManager> instance;

	bool terminado = true;
};


#endif
