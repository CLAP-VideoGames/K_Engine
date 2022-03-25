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
#include <physics_prj/CollisionLayers.h>
#include <render_prj/RenderManager.h>
#include <sound_prj/AudioManager.h>
#include <input_prj/InputManager.h>
#include <ui_prj/UIManager.h>

#include <ecs_prj/EntityManager.h>
#include <ecs_prj/ComponentManager.h>
#include <ecs_prj/Entity.h>

#include <components_prj/Transform.h>
#include <components_prj/RigidBody.h>
#include <components_prj/MeshRenderer.h>
#include <components_prj/AudioSource.h>

#include <utils_prj/KTimer.h>
#include <utils_prj/KVector3.h>
#include <utils_prj/KMath.h>

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
			K_Engine::KTimer timer = K_Engine::KTimer();

			// Render Manager initialisation
			K_Engine::RenderManager::Init("K_Engine"); //GetInstance() returns nullptr if Init isnt called first
			K_Engine::RenderManager* renderMan = K_Engine::RenderManager::GetInstance();
			//renderMan->exampleScene();

			// Physics Manager initialisation
			K_Engine::PhysicsManager::Init(20, { 0, -9.8, 0 }); //GetInstance() returns nullptr if Init isnt called first
			K_Engine::PhysicsManager* physicsMan = K_Engine::PhysicsManager::GetInstance();


			std::string playerLayer = "Player";
			std::string nothingLayer = "Nothing";
			std::string platformLayer = "Platform";

			physicsMan->addLayer(playerLayer);
			physicsMan->addLayer(nothingLayer);
			physicsMan->addLayer(platformLayer);
			// UI Manager initialisation
			K_Engine::UIManager::Init("K_EngineUI");
			K_Engine::UIManager* uiMan = K_Engine::UIManager::GetInstance();
			/*uiMan->addText("Hola",
				std::pair<float,float>(0,0));
			
				CEGUI::ProgressBar * pr = 
			uiMan->addProgressBar(std::pair<float,float>(0.5,0.5),
				std::pair<float, float>(0.3, 0.1));*/

			/*uiMan->addButton("BUTTON", std::pair<float, float>(0.5, 0.5),
				std::pair<float, float>(0.3, 0.1));*/

			uiMan->debug();

			/*uiMan->createSlider(std::pair<float, float>(0.2f, 0.2f), std::pair<float, float>(0.1f, 0.1f));
			uiMan->createScrollbar(std::pair<float, float>(0.7f, 0.7f), std::pair<float, float>(0.1f, 0.1f));*/
			//uiMan->exampleUI();

			// Audio Manager initialisation
			K_Engine::AudioManager::Init();
			K_Engine::AudioManager* audioMan = K_Engine::AudioManager::GetInstance();

			// Input Manager initialisation
			K_Engine::InputManager::Init();
			K_Engine::InputManager* inputMan = K_Engine::InputManager::GetInstance();

			inputMan->setDeathZones(5000, 0);

			// Component Manager initialisation(Como "Lectura de un mapa")
			ComponentManager::Init("K_EngineComponents");
			ComponentManager* compMan = ComponentManager::GetInstance();

			//Initialization of the base components
			compMan->add<Transform>();
			compMan->add<MeshRenderer>();
			compMan->add<RigidBody>();
			compMan->add<AudioSource>();

			int playerCollidesWith = physicsMan->getLayerValue(platformLayer);
			//Configurations Scope
			EntityManager* entMan = new EntityManager(); // Entity Manager
			Entity* player = entMan->addEntity();
			{
				Transform* t = player->addComponent<Transform>(); t->setDimensions(3.0f);
				t->setPosition(-2, 5, 0);
				ColliderType boxType = ColliderType::CT_SPHERE;
				BodyType bodyType =  BodyType::BT_DYNAMIC;
				float mass = 1.0f;
				RigidBody* r = player->addComponent<RigidBody>(boxType, bodyType, mass, physicsMan->getLayerValue(playerLayer), playerCollidesWith);
				r->setFriction(0.6f);
				r->setRestitution(1.2f);
				MeshRenderer* m = player->addComponent<MeshRenderer>();
				m->setMesh("sphere.mesh");
				m->setMaterial("K_Engine/PrototypeBlue");
				m->debug();
			}

			Entity* playerChild = entMan->addEntity();
			{
				Transform* t = playerChild->addComponent<Transform>(); t->setDimensions(3.0f);
				t->setPosition(3, 6, 0);
				t->setRotation(0, 0, 10);
				ColliderType boxType = ColliderType::CT_SPHERE;
				BodyType bodyType =  BodyType::BT_DYNAMIC;
				float mass = 1.0f;
				//RigidBody* r = playerChild->addComponent<RigidBody>(boxType, bodyType, mass, physicsMan->getLayerValue(playerLayer), playerCollidesWith);
				//r->setFriction(0.6f);
				//r->setRestitution(1.2f);
				MeshRenderer* m = playerChild->addComponent<MeshRenderer>();
				m->setMesh("sphere.mesh");
				m->setMaterial("K_Engine/PrototypeBlue");
				m->debug();
			}
			player->addChild(playerChild);
			
			int platformCollidesWith = physicsMan->getLayerValue(playerLayer);
			//Configurations Scope
			{
				Entity* platform = entMan->addEntity();
				Transform* t = platform->addComponent<Transform>(); t->setDimensions(5.f, 1.0f, 5.f);
				t->setPosition(-2.8, 0.f, 0);
				t->setRotation(0, 0, -45);
				ColliderType boxType = ColliderType::CT_BOX;
				BodyType bodyType = BodyType::BT_STATIC;
				RigidBody* r = platform->addComponent<RigidBody>(boxType, bodyType, 0.0f, physicsMan->getLayerValue(platformLayer), platformCollidesWith);
				r->setRestitution(0.8f);
				MeshRenderer* m = platform->addComponent<MeshRenderer>();
				m->setMesh("cube.mesh");
				m->setMaterial("K_Engine/PrototypeOrange");
			}
			int futureCollidesWith = physicsMan->getLayerValue(playerLayer);
			//Configurations Scope
			{
				Entity* platform = entMan->addEntity();
				Transform* t = platform->addComponent<Transform>(); t->setDimensions(5.f, 1.0f, 5.f);
				t->setPosition(2.8, 0.f, 0);
				t->setRotation(0, 0, 45);
				ColliderType boxType = ColliderType::CT_BOX;
				BodyType bodyType = BodyType::BT_STATIC;
				RigidBody* r = platform->addComponent<RigidBody>(boxType, bodyType, 0.0f, physicsMan->getLayerValue(platformLayer), futureCollidesWith);
				r->setRestitution(0.8f);
				MeshRenderer* m = platform->addComponent<MeshRenderer>();
				m->setMesh("cube.mesh");
				m->setMaterial("K_Engine/PrototypeOrange");
			}

			{
				/*Entity* audio = entMan->addEntity();
				AudioSource* a = audio->addComponent<AudioSource>();
				//a->playSong("./assets/sounds/samba_UCM.ogg");
				a->playSoundEffect("./assets/sounds/clap.wav",-1);
				a->setGeneralVolume(35);
				a->stopOneSoundEffect("./assets/sounds/clap.wav");*/
			}

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

					run = (!inputMan->controllerButtonPressed(K_Engine::CONTROLLER_BUTTON_B)
						&& !inputMan->isKeyDown(K_Engine::SCANCODE_ESCAPE));
						
					uiMan->update();
					entMan->update();
					physicsMan->update();
					accFrameTime -= DELTA_TIME;
				}

				renderMan->render();
			}

			K_Engine::AudioManager::Shutdown();
			K_Engine::UIManager::Shutdown();
			K_Engine::PhysicsManager::Shutdown();
			K_Engine::RenderManager::Shutdown();
			delete entMan;
		}
		catch (Ogre::Exception& e) {
			Ogre::LogManager::getSingleton().logMessage("An exception has occured: " + e.getFullDescription() + "\n");
		}

		return 0;
	}