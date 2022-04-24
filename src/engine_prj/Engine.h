#pragma once
#ifndef ENGINE_H
#define ENGINE_H

#include <windows.h>
#include <string>

namespace K_Engine {
	class Scene;
	typedef Scene* (*SceneLoad)();
	typedef void (*GameComponents)();

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

		K_Engine::RenderManager* getRenderManager();
		K_Engine::PhysicsManager* getPhysicsManager();
		K_Engine::UIManager* getUIManager();
		K_Engine::AudioManager* getAudioManager();
		K_Engine::InputManager* getInputManager();
		K_Engine::ComponentManager* getComponentManager();
		K_Engine::SceneManager* getSceneManager();

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
		SceneLoad loadScene;
		GameComponents registerGameComponents;

		bool loadGame();
		bool closeGame();

		// Debug section
		// THIS SHOULD BE DELETED EVENTUALLY UPON ENGINE RELEASE
		void debug();
	};
}
#endif // ENGINE_H