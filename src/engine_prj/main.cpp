#include <stdio.h>
#include <iostream>
#ifndef _DEBUG
#include <windows.h>
#endif

#include <engine_prj/Engine.h>

#ifdef _DEBUG
int main() {
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif
#ifndef _DEBUG
int WINAPI WinMain(HINSTANCE zHInstance, HINSTANCE prevInstance, LPSTR lpCmdLine, int nCmdShow) {
#endif

	K_Engine::Engine engine = K_Engine::Engine("K_Engine");

	if (engine.init()) {
		try {
			engine.setup();
			engine.run();
		}
		catch (const std::exception& e) {
			std::cout << "Error on engine setup or runtime\n";
		}
	}
	else
		std::cout << "Error on engine initialisation\n";

	if(!engine.shutdown())
		std::cout << "Error on engine shutdown\n";

	return 0;
}