#include <stdio.h>
#include <iostream>
#ifndef _DEBUG
#include <windows.h>
#endif

#include <OgreLogManager.h>
#include "BulletDynamics/Dynamics/btDiscreteDynamicsWorld.h"

// this should be on the render project, before the SDL.h,
// but since it's here I put it there temporarily
#define SDL_MAIN_HANDLED
#include <SDL_timer.h>
#include <SDL.h>

#include <physics_prj/PhysicsManager.h>
#include <render_prj/RenderManager.h>
#include <sound_prj/AudioManager.h>
#include <ecs_prj/EntityManager.h>
#include <ui_prj/UIManager.h>

#define DELTA_TIME 33

bool pollEvents()
{
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
			std::cout << "exit\n";
			return false;
			break;
		default:
			break;
		}
	}
	return true;
}

#ifdef _DEBUG
int main() {
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif
#ifndef _DEBUG
	int WINAPI WinMain(HINSTANCE zHInstance, HINSTANCE prevInstance, LPSTR lpCmdLine, int nCmdShow) {
#endif

	try {
		// Render Manager initialisation
		RenderManager::Init("K_Engine"); //GetInstance() returns nullptr if Init isnt called first
		RenderManager* renderMan = RenderManager::GetInstance();
		renderMan->exampleScene();

		// Physics Manager initialisation
		PhysicsManager::Init(10, 20, { 0, -9.8, 0}); //GetInstance() returns nullptr if Init isnt called first
		PhysicsManager* physicsMan = PhysicsManager::GetInstance();
		physicsMan->exampleObjects();
		
		// UI Manager initialisation
		UIManager::Init("K_EngineUI");
		UIManager* uiMan = UIManager::GetInstance();

		// Audio Manager initialisation
		AudioManager::Init();
		AudioManager* audioMan = AudioManager::GetInstance();
		//audioMan->playWAV("./assets/sounds/clap.wav");
		audioMan->playMUS("./assets/sounds/clapV2.ogg");

		bool run = true; // time --> miliseconds
		unsigned int accFrameTime = 0, currTime = SDL_GetTicks();
		int cycles = 10000;
		while (run) {
			unsigned int frame = SDL_GetTicks() - currTime;
			currTime += frame;

			accFrameTime += frame;
			while (accFrameTime >= DELTA_TIME) {
				// get input here (clear and check same time)
				// TEMPORAL
				run = pollEvents();
				//physicsMan->Update();
				accFrameTime -= DELTA_TIME;
			}

			renderMan->render();
		}

		AudioManager::Shutdown();
		UIManager::Shutdown();
		PhysicsManager::Shutdown();
		RenderManager::Shutdown();
	}
	catch (Ogre::Exception& e) {
		Ogre::LogManager::getSingleton().logMessage("An exception has occured: " + e.getFullDescription() + "\n");
	}

	return 0;
}