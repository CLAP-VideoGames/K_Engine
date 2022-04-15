#include "Engine.h"

#define DEVELOPMENT

#include <stdio.h>
#include <iostream>

#include <physics_prj/PhysicsManager.h>
#include <physics_prj/CollisionLayers.h>

#include <render_prj/RenderManager.h>
#include <sound_prj/AudioManager.h>
#include <input_prj/InputManager.h>
#include <scene_prj/SceneManager.h>
#include <log_prj/LogManager.h>
#include <ui_prj/UIManager.h>
#include <script_prj/ScriptManager.h>

// DELETE
#include <scene_prj/Scene.h>

#include <ecs_prj/ComponentManager.h>
#include <components_prj/ComponentRegistry.h>

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
		success = K_Engine::RenderManager::Init(name) &&
			K_Engine::PhysicsManager::Init(name + "Physics", { 0, -9.8, 0 }) &&
			K_Engine::AudioManager::Init() &&
			K_Engine::InputManager::Init() &&
			K_Engine::ScriptManager::Init(name + "Script") &&
			K_Engine::ComponentManager::Init(name + "Components") &&
			K_Engine::SceneManager::Init(name + "Scene") &&
			K_Engine::LogManager::Init() && 
			K_Engine::UIManager::Init(name + "UI");

		// if something goes wrong, we exit initialization
		if (!success) return false;

		// acquisition of sub-engine's instances
		renderMan = K_Engine::RenderManager::GetInstance();
		physicsMan = K_Engine::PhysicsManager::GetInstance();
		uiMan = K_Engine::UIManager::GetInstance();
		scriptMan = K_Engine::ScriptManager::GetInstance();
		audioMan = K_Engine::AudioManager::GetInstance();
		inputMan = K_Engine::InputManager::GetInstance();
		compMan = K_Engine::ComponentManager::GetInstance();
		sceneMan = K_Engine::SceneManager::GetInstance();
		logMan = K_Engine::LogManager::GetInstance();
	}

	void Engine::setup()
	{
		// render setup
		renderMan->locateResources();

		// physics setup
		std::string playerLayer = "Player";
		std::string nothingLayer = "Nothing";
		std::string platformLayer = "Platform";

		physicsMan->addLayer(playerLayer);
		physicsMan->addLayer(nothingLayer);
		physicsMan->addLayer(platformLayer);

		// input setup
		inputMan->setDeathZones(5000, 0);

		// ui setup
		uiMan->debug();

		// base components setup
		K_Engine::Registry::registerComponents();

#ifndef DEVELOPMENT
		registerGameComponents();
		sceneMan->pushScene(loadScene());
#endif
#ifdef DEVELOPMENT
		// THIS SHOULD BE DELETED EVENTUALLY UPON ENGINE RELEASE
		debug();
#endif
	}

	void Engine::run()
	{
		// Timer for main loop
		K_Engine::Timer timer = K_Engine::Timer();

		bool run = true; // time --> miliseconds
		unsigned int accFrameTime = 0, currTime = timer.currTime();
		while (run) {
			unsigned int frameTime = timer.currTime() - currTime;
			currTime += frameTime;

			accFrameTime += frameTime;

			while (accFrameTime >= DELTA_TIME) {
				inputMan->update();

				run = (!inputMan->controllerButtonPressed(K_Engine::CONTROLLER_BUTTON_B)
					&& !inputMan->isKeyDown(K_Engine::SCANCODE_ESCAPE));

				/*if (inputMan->isKeyDown(K_Engine::SCANCODE_0)) {
					K_Engine::Vector3 scal = t->getScale();
					t->setScale(3, 3, 3);
				}*/

				//Physics update
				sceneMan->fixedUpdateScene(DELTA_TIME);
				physicsMan->update();
				accFrameTime -= DELTA_TIME;
			}

			//Regular update for the entities
			sceneMan->updateScene(frameTime);
			uiMan->update();
			renderMan->render();
		}
	}

	bool Engine::shutdown()
	{
		bool success = K_Engine::SceneManager::Shutdown() &&
			K_Engine::AudioManager::Shutdown() &&
			K_Engine::ScriptManager::Shutdown() &&
			K_Engine::UIManager::Shutdown() &&
			K_Engine::PhysicsManager::Shutdown() &&
			K_Engine::RenderManager::Shutdown();

		sceneMan = nullptr; renderMan = nullptr;
		physicsMan = nullptr; uiMan = nullptr; 
		audioMan = nullptr; scriptMan = nullptr;
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

		loadScene = (SceneLoad)GetProcAddress(game, "loadScene");
		registerGameComponents = (GameComponents)GetProcAddress(game, "registerComponents");

		return loadScene != nullptr || registerGameComponents != nullptr;
	}

	K_Engine::RenderManager* Engine::getRenderManager()
	{
		return renderMan;
	}

	K_Engine::PhysicsManager* Engine::getPhysicsManager()
	{
		return physicsMan;
	}

	K_Engine::UIManager* Engine::getUIManager()
	{
		return uiMan;
	}

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