#pragma once
#ifndef ENGINE_H
#define ENGINE_H

#include <windows.h>
#include <string>

namespace K_Engine {
	class Scene;
	typedef void (*Game)();
	typedef Scene* (*SceneLoad)();
	typedef std::string (*GameName)();

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
		GameName gameName;
		Game registerGameComponents;
		Game registerGameLayers;
		SceneLoad loadScene;

		bool loadGame();
		bool closeGame();

		// Debug section
		// THIS SHOULD BE DELETED EVENTUALLY UPON ENGINE RELEASE
		void debug();
	};
}
#endif // ENGINE_H