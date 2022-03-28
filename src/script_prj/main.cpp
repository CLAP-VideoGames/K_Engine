// C++ program to illustrate the use of
// LuaCpp library
#include <stdio.h>
#include <iostream>

#include "ScriptManager.h"


int main() {
	K_Engine::ScriptManager::Init("KEngineScripting");
	K_Engine::ScriptManager* scriptMan = K_Engine::ScriptManager::GetInstance();
	
	scriptMan->reloadLuaScript("test");

	scriptMan = nullptr;
	K_Engine::ScriptManager::Shutdown();

	return 0;
}
