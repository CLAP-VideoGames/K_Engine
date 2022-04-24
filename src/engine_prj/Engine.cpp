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

#include <utils_prj/Math.h>
#include <utils_prj/Timer.h>
#include <utils_prj/Vector3.h>
#include <utils_prj/checkML.h>

#define DELTA_TIME 33 // 33 ms = 1/60 s

namespace K_Engine {
	Engine::Engine() {
		name = "K_Engine";
	}

	Engine::~Engine() = default;

	bool Engine::init() {
		// init log manager
		bool success = K_Engine::LogManager::Init();
		if (!success) // can't print anything if this fails, so we just return 
			return false;
		logMan = K_Engine::LogManager::GetInstance();

#ifndef DEVELOPMENT
		// load game dll
		success = loadGame();

		// if something goes wrong, we exit initialization
		if (!success) 
			return logMan->printLog(LogType::FATAL, "Error on game data initialization");
#endif

		// initialisation of all sub-engines
		success = K_Engine::RenderManager::Init(name) &&
			K_Engine::UIManager::Init() &&
			K_Engine::PhysicsManager::Init({ 0, -9.8, 0 }) &&
			K_Engine::AudioManager::Init() &&
			K_Engine::ScriptManager::Init() &&
			K_Engine::InputManager::Init() &&
			K_Engine::SceneManager::Init() &&
			K_Engine::ComponentManager::Init();

		// if something goes wrong, we exit initialization
		if (!success)
			return logMan->printLog(LogType::FATAL, "Error on sub-engines initialization");

		// acquisition of sub-engine's instances
		renderMan = K_Engine::RenderManager::GetInstance();
		physicsMan = K_Engine::PhysicsManager::GetInstance();
		uiMan = K_Engine::UIManager::GetInstance();
		audioMan = K_Engine::AudioManager::GetInstance();
		scriptMan = K_Engine::ScriptManager::GetInstance();
		inputMan = K_Engine::InputManager::GetInstance();
		sceneMan = K_Engine::SceneManager::GetInstance();
		compMan = K_Engine::ComponentManager::GetInstance();

		return logMan->printLog(LogType::INFO, "Engine initialization success\n");
	}

	bool Engine::setup()
	{
		// render setup
		uiMan->cleanElements();
		renderMan->locateResources("./resources.cfg");

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
		K_Engine::Registry::registerComponents();

#ifndef DEVELOPMENT
		registerGameComponents();
		sceneMan->pushScene(loadScene());
#endif

#ifdef DEVELOPMENT
		// THIS SHOULD BE DELETED EVENTUALLY UPON ENGINE RELEASE
		debug();
#endif

		return logMan->printLog(LogType::INFO, "Engine setup success\n");
	}

	void Engine::run()
	{
		// Timer for main loop
		K_Engine::Timer timer = K_Engine::Timer();

		bool run = true; // time --> miliseconds
		unsigned int accFrameTime = 0, currTime = timer.currTime();
		while (run) {
			unsigned int frameTime = timer.currTime() - currTime;
			currTime += frameTime; accFrameTime += frameTime;

			logMan->clearLogBuffer();
			while (accFrameTime >= DELTA_TIME) {
				inputMan->update();

				run = (!inputMan->controllerButtonPressed(K_Engine::CONTROLLER_BUTTON_B)
					&& !inputMan->isKeyDown(K_Engine::SCANCODE_ESCAPE));

				// physics update
				sceneMan->fixedUpdateScene(DELTA_TIME);
				physicsMan->update();
				accFrameTime -= DELTA_TIME;
			}

			// regular update for the entities
			sceneMan->updateScene(frameTime);
			uiMan->update();
			renderMan->render();

			logMan->printLogBuffer();
		}
	}

	bool Engine::shutdown()
	{
		bool success = K_Engine::ComponentManager::Shutdown() &&
			K_Engine::InputManager::Shutdown() &&
			K_Engine::ScriptManager::Shutdown() &&
			K_Engine::AudioManager::Shutdown() &&
			K_Engine::UIManager::Shutdown() &&
			K_Engine::PhysicsManager::Shutdown() &&
			K_Engine::SceneManager::Shutdown() && // after PhysicsManager because if not it'd mean runtime error on callbacks
			K_Engine::RenderManager::Shutdown();
		
		if(!success)
			return logMan->printLog(LogType::WARNING, "Error on sub-modules shutdown");

		sceneMan = nullptr; renderMan = nullptr;
		physicsMan = nullptr; uiMan = nullptr;
		audioMan = nullptr; scriptMan = nullptr;
		inputMan = nullptr; compMan = nullptr;

#ifndef DEVELOPMENT
		success = closeGame();
#endif
		if (!success)
			return logMan->printLog(LogType::WARNING, "Error on game data shutdown");
		logMan->printLog(LogType::INFO, "Engine shutdown success");

		K_Engine::LogManager::Shutdown(); logMan = nullptr;

		return success;
	}

	bool Engine::loadGame()
	{
		// game .dll loading
#ifndef _DEBUG
		game = LoadLibrary(TEXT("./game.dll"));
#endif 
#ifdef _DEBUG
		game = LoadLibrary(TEXT("./game_d.dll"));
#endif 

		if (game == nullptr)
			return logMan->addLog(LogType::FATAL, "Game .dll unable to load");
		logMan->addLog(LogType::FATAL, "Game load success");

		// game functions load
		loadScene = (SceneLoad)GetProcAddress(game, "loadScene");
		registerGameComponents = (GameComponents)GetProcAddress(game, "registerComponents");

		if (loadScene != nullptr || registerGameComponents != nullptr)
			return logMan->addLog(LogType::FATAL, "One of game .dll functions unable to load explicitly");
		return logMan->addLog(LogType::FATAL, "Game functions load success");
	}

	bool Engine::closeGame()
	{
		try {
			FreeLibrary(game);
		}
		catch (const std::exception& e) {
			return false;
		}

		return true;
	}

	void Engine::debug()
	{
		Scene* exampleScene = new Scene();
		exampleScene->debug();
		sceneMan->pushScene(exampleScene);
	}
}