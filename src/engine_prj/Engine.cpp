#include "Engine.h"

#include <stdio.h>
#include <iostream>

//Just for testing
// this should be on the render project, before the SDL.h,
// but since it's here I put it there temporarily
#include <OgreLogManager.h>

#include <physics_prj/PhysicsManager.h>
#include <physics_prj/CollisionLayers.h>

#include <render_prj/RenderManager.h>
#include <sound_prj/AudioManager.h>
#include <input_prj/InputManager.h>
//#include <ui_prj/UIManager.h>
#include <scene_prj/SceneManager.h>
#include <log_prj/LogManager.h>

#define DEVELOPMENT

// DELETE
#include <scene_prj/Scene.h>

#include <ecs_prj/ComponentManager.h>
#include <components_prj/Transform.h>
#include <components_prj/RigidBody.h>
#include <components_prj/MeshRenderer.h>
#include <components_prj/AudioSource.h>

#include <utils_prj/Timer.h>
#include <utils_prj/Vector3.h>
#include <utils_prj/Math.h>

#define DELTA_TIME 33 // 33 ms = 1/60 s

namespace K_Engine {
	Engine::Engine(std::string n) {
		name = n;
	}

	Engine::~Engine() = default;

	bool Engine::init() {
		bool success;

#ifndef DEVELOPMENT
		// load game dll
		success = loadGame();

		// if something goes wrong, we exit initialization
		if (!success) return false;
#endif

		// initialisation of all sub-engines
		success = K_Engine::RenderManager::Init(name + "Render") &&
			K_Engine::PhysicsManager::Init(20, { 0, -9.8, 0 }) &&
			/*K_Engine::UIManager::Init(name + "UI") &&*/
			K_Engine::AudioManager::Init() &&
			K_Engine::InputManager::Init() &&
			K_Engine::ComponentManager::Init(name + "Components") &&
			K_Engine::SceneManager::Init(name + "Components") &&
			K_Engine::LogManager::Init();

		// if something goes wrong, we exit initialization
		if (!success) return false;

		// acquisition of sub-engine's instances
		renderMan = K_Engine::RenderManager::GetInstance();
		physicsMan = K_Engine::PhysicsManager::GetInstance();
		//uiMan = K_Engine::UIManager::GetInstance();
		audioMan = K_Engine::AudioManager::GetInstance();
		inputMan = K_Engine::InputManager::GetInstance();
		compMan = K_Engine::ComponentManager::GetInstance();
		sceneMan = K_Engine::SceneManager::GetInstance();
		logMan = K_Engine::LogManager::GetInstance();
	}

	void Engine::setup()
	{
		// physics setup
		std::string playerLayer = "Player";
		std::string nothingLayer = "Nothing";
		std::string platformLayer = "Platform";

		physicsMan->addLayer(playerLayer);
		physicsMan->addLayer(nothingLayer);
		physicsMan->addLayer(platformLayer);

		// input setup
		inputMan->setDeathZones(5000, 0);

		// base components setup
		compMan->add<K_Engine::Transform>();
		compMan->add<K_Engine::MeshRenderer>();
		compMan->add<K_Engine::RigidBody>();
		compMan->add<K_Engine::AudioSource>();

#ifdef DEVELOPMENT
		// THIS SHOULD BE DELETED EVENTUALLY UPON ENGINE RELEASE
		debug();
#endif
#ifndef DEVELOPMENT
		sceneMan->pushScene(load());
#endif
	}

	void Engine::run()
	{
		// Timer for main loop
		K_Engine::Timer timer = K_Engine::Timer();

		bool run = true; // time --> miliseconds
		unsigned int accFrameTime = 0, currTime = timer.currTime();
		while (run) {
			unsigned int frame = timer.currTime() - currTime;
			currTime += frame;

			accFrameTime += frame;
			while (accFrameTime >= DELTA_TIME) {
				inputMan->update();

				run = (!inputMan->controllerButtonPressed(K_Engine::CONTROLLER_BUTTON_B)
					&& !inputMan->isKeyDown(K_Engine::SCANCODE_ESCAPE));

				/*if (inputMan->isKeyDown(K_Engine::SCANCODE_0)) {
					K_Engine::Vector3 scal = t->getScale();
					t->setScale(3, 3, 3);
				}*/

				//Physics update
				sceneMan->fixedUpdateScene();
				physicsMan->update();
				accFrameTime -= DELTA_TIME;
			}

			//Regular update for the entities
			sceneMan->updateScene();
			//uiMan->update();
			renderMan->render();
		}
	}

	bool Engine::shutdown()
	{
		bool success = K_Engine::SceneManager::Shutdown() &&
			K_Engine::AudioManager::Shutdown() &&
			//K_Engine::UIManager::Shutdown() &&
			K_Engine::PhysicsManager::Shutdown() &&
			K_Engine::RenderManager::Shutdown();

		sceneMan = nullptr; renderMan = nullptr; physicsMan = nullptr;
		/*uiMan = nullptr;*/ audioMan = nullptr;
		inputMan = nullptr; compMan = nullptr;

#ifndef DEVELOPMENT
		FreeLibrary(game);
#endif

		return success;
	}

	bool Engine::loadGame()
	{
#ifndef _DEBUG
		HMODULE game = LoadLibrary(TEXT("./game.dll"));
#endif // !_DEBUG
#ifdef _DEBUG
		game = LoadLibrary(TEXT("./game_d.dll"));
#endif // !_DEBUG

		load = (SceneLoad)GetProcAddress(game, "loadScene");

		return load != nullptr;
	}

	K_Engine::RenderManager* Engine::getRenderManager()
	{
		return renderMan;
	}

	K_Engine::PhysicsManager* Engine::getPhysicsManager()
	{
		return physicsMan;
	}

	/*K_Engine::UIManager* Engine::getUIManager()
	{
		return uiMan;
	}*/

	K_Engine::AudioManager* Engine::getAudioManager()
	{
		return audioMan;
	}

	K_Engine::InputManager* Engine::getInputManager()
	{
		return inputMan;
	}

	K_Engine::ComponentManager* Engine::getComponentManager()
	{
		return compMan;
	}

	K_Engine::SceneManager* Engine::getSceneManager()
	{
		return sceneMan;
	}

	void Engine::debug()
	{
		// ui debug
		//uiMan->debug();

		//uiMan->createSlider(std::pair<float, float>(0.2f, 0.2f), std::pair<float, float>(0.1f, 0.1f));
		//uiMan->createScrollbar(std::pair<float, float>(0.7f, 0.7f), std::pair<float, float>(0.1f, 0.1f));
		//uiMan->addText("Hola", std::pair<float, float>(0, 0));
		//CEGUI::ProgressBar* pr = uiMan->addProgressBar(std::pair<float, float>(0.5, 0.5), std::pair<float, float>(0.3, 0.1));
		//uiMan->addButton("BUTTON", std::pair<float, float>(0.5, 0.5), td::pair<float, float>(0.3, 0.1));
		//uiMan->exampleUI();

		Scene* exampleScene = new Scene();
		exampleScene->debug();
		sceneMan->pushScene(exampleScene);
	}
}