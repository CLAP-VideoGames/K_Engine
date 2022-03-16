#include <stdio.h>
#include <iostream>
#ifndef _DEBUG
#include <windows.h>
#endif

//Just for testing
// this should be on the render project, before the SDL.h,
// but since it's here I put it there temporarily
#include <OgreLogManager.h>

#include <physics_prj/PhysicsManager.h>
#include <render_prj/RenderManager.h>
#include <sound_prj/AudioManager.h>
#include <input_prj/InputManager.h>
#include <ui_prj/UIManager.h>

#include <ecs_prj/EntityManager.h>
#include <ecs_prj/ComponentManager.h>
#include <ecs_prj/Entity.h>
#include <ecs_prj/Transform.h>
#include <ecs_prj/RigidBody.h>
#include <ecs_prj/MeshRenderer.h>

#include <utils_prj/EngineTimer.h>
#include <utils_prj/CustomVector3.h>

//Temporary
#include <iostream>
#include <string>

#define DELTA_TIME 33

#ifdef _DEBUG
int main() {
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif
#ifndef _DEBUG
	int WINAPI WinMain(HINSTANCE zHInstance, HINSTANCE prevInstance, LPSTR lpCmdLine, int nCmdShow) {
#endif

		try {
			// Timer for main loop
			EngineTimer timer = EngineTimer();

			// Render Manager initialisation
			RenderManager::Init("K_Engine"); //GetInstance() returns nullptr if Init isnt called first
			RenderManager* renderMan = RenderManager::GetInstance();
			//renderMan->exampleScene();

			// Physics Manager initialisation
			PhysicsManager::Init(10, 20, { 0, -9.8, 0 }); //GetInstance() returns nullptr if Init isnt called first
			PhysicsManager* physicsMan = PhysicsManager::GetInstance();

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

			// Component Manager initialisation(Como "Lectura de un mapa")
			ComponentManager::Init("K_EngineComponents");
			EntityManager* entMan = new EntityManager(); // Entity Manager
			Entity* e = entMan->addEntity();
			Component* t = e->addComponent<Transform>(); t->debug();
			Component* m = e->addComponent<MeshRenderer>(); m->debug();
			ColliderType boxType = ColliderType::CT_BOX;
			Component* r = e->addComponent<RigidBody>(boxType);


			entMan->start();

			bool run = true; // time --> miliseconds
			unsigned int accFrameTime = 0, currTime = timer.currTime();
			int cycles = 10000;
			while (run) {
				unsigned int frame = timer.currTime() - currTime;
				currTime += frame;

				accFrameTime += frame;
				while (accFrameTime >= DELTA_TIME) {
					inputMan->update();

					//if (inputMan->getLeftMouseButtonPressed()) {
					//	run = false;
					//}
					
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