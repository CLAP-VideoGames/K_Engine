#include <stdio.h>
#include <iostream>
#ifndef _DEBUG
#include <windows.h>
#endif

#include <engine_prj/Engine.h>

#ifdef _DEBUG
int main() {
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	//_CrtSetBreakAlloc(39400); // id of the new we are trying to delete correctly (use it when checkML doesn't work)
#endif
#ifndef _DEBUG
int WINAPI WinMain(HINSTANCE zHInstance, HINSTANCE prevInstance, LPSTR lpCmdLine, int nCmdShow) {
#endif
	K_Engine::Engine engine = K_Engine::Engine();

	if (engine.init() && engine.setup()) {
		engine.run();
		engine.shutdown();
	}

	return 0;
}