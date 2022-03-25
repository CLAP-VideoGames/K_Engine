#include "LogManager.h"

#include <OgreRoot.h>
#include <OgreLog.h>
#include <OgreLogManager.h>

std::unique_ptr<LogManager> LogManager::instance = nullptr;

LogManager::LogManager() = default;

LogManager::~LogManager() = default;

LogManager* LogManager::GetInstance() {
	return instance.get();
}