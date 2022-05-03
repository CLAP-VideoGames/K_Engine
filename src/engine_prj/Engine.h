#pragma once
#ifndef ENGINE_H
#define ENGINE_H

#include <windows.h>
#include <string>

namespace K_Engine {
	class Scene;
	typedef void (*Game)();
	typedef Scene* (*GameScene)();
	typedef bool (*GameBool)();
	typedef std::string (*GameString)();

	class RenderManager;
	class PhysicsManager;
	class UIManager;
	class AudioManager;
	class InputManager;
	class ComponentManager;
	class SceneManager;
	class LogManager;
	class UIManager;
	class ScriptManager;

	class __declspec(dllexport) Engine {
	public:
		Engine();
		~Engine();

		bool init();
		bool setup();
		void run();
		bool shutdown();

	private:
		std::string name;

		K_Engine::RenderManager* renderMan;
		K_Engine::PhysicsManager* physicsMan;
		K_Engine::ScriptManager* scriptMan;
		K_Engine::AudioManager* audioMan;
		K_Engine::InputManager* inputMan;
		K_Engine::ComponentManager* compMan;
		K_Engine::SceneManager* sceneMan;
		K_Engine::LogManager* logMan;
		K_Engine::UIManager* uiMan;

		HMODULE game;
		GameString gameName;
		GameString startUpScene;
		Game registerGameComponents;
		Game registerGameLayers;
		GameBool gameExitConditions;

		// DELETE
		GameScene startScene;

		bool exit();

		bool loadGame();
		bool closeGame();
	};
}
#endif // ENGINE_H