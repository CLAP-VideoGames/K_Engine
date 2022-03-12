#include <stdio.h>
#include <iostream>
#ifndef _DEBUG
#include <windows.h>
#endif

//Just for testing
// this should be on the render project, before the SDL.h,
// but since it's here I put it there temporarily
#include "BulletDynamics/Dynamics/btDiscreteDynamicsWorld.h"
#include <SDL_timer.h>
#include <OgreLogManager.h>

#include <physics_prj/PhysicsManager.h>
#include <render_prj/RenderManager.h>
#include <sound_prj/AudioManager.h>
#include <input_prj/InputManager.h>
#include <ecs_prj/EntityManager.h>
#include <ecs_prj/ComponentManager.h>
#include <ecs_prj/Entity.h>
#include <ecs_prj/Transform.h>
#include <ecs_prj/MeshRenderer.h>
#include <ui_prj/UIManager.h>

#define DELTA_TIME 33

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
			//renderMan->exampleScene();

			// Physics Manager initialisation
			PhysicsManager::Init(10, 20, { 0, -9.8, 0 }); //GetInstance() returns nullptr if Init isnt called first
			PhysicsManager* physicsMan = PhysicsManager::GetInstance();
			physicsMan->exampleObjects();

			// UI Manager initialisation
			UIManager::Init("K_EngineUI");
			UIManager* uiMan = UIManager::GetInstance();
			uiMan->exampleUI();

			// Audio Manager initialisation
			AudioManager::Init();
			AudioManager* audioMan = AudioManager::GetInstance();
			//audioMan->playWAV("./assets/sounds/clap.wav");
			audioMan->playMUS("./assets/sounds/clapV2.ogg");

			// Input Manager initialisation
			InputManager::Init();
			InputManager* inputMan = InputManager::GetInstance();

			//ComponentManager Initialization
			ComponentManager::Init("K_EngineComponents");
			//ComponentManager* compMan = ComponentManager::GetInstance();

			//Entity Manager
			EntityManager* entMan = new EntityManager();
			Entity* e = entMan->addEntity();
			Transform* t = e->addComponent<Transform>();
			t->setScale(0.2, 0.2, 0.2);
			e->addComponent<MeshRenderer>();

			bool run = true; // time --> miliseconds
			unsigned int accFrameTime = 0, currTime = SDL_GetTicks();
			int cycles = 10000;
			while (run) {
				unsigned int frame = SDL_GetTicks() - currTime;
				currTime += frame;

				accFrameTime += frame;
				while (accFrameTime >= DELTA_TIME) {
					// get input here (clear and check same time)			
					run = inputMan->update();
					//physicsMan->Update();
					accFrameTime -= DELTA_TIME;
				}

				renderMan->render();
			}

			AudioManager::Shutdown();
			UIManager::Shutdown();
			PhysicsManager::Shutdown();
			RenderManager::Shutdown();
			delete entMan;
		}
		catch (Ogre::Exception& e) {
			Ogre::LogManager::getSingleton().logMessage("An exception has occured: " + e.getFullDescription() + "\n");
		}

		return 0;
	}