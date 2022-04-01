#pragma once
#ifndef ENGINE_H
#define ENGINE_H

#include <string>
#include <windows.h>

namespace K_Engine {
	class Scene;
	class Engine;
	typedef Scene* (*SceneLoad)();

	class RenderManager;
	class PhysicsManager;
	//class UIManager;
	class AudioManager;
	class InputManager;
	class ComponentManager;
	class SceneManager;
	class LogManager;

	class __declspec(dllexport) Engine {
	public:
		Engine(std::string n);
		~Engine();

		bool init();
		void setup();
		void run();
		bool shutdown();

		K_Engine::RenderManager* getRenderManager();
		K_Engine::PhysicsManager* getPhysicsManager();
		//K_Engine::UIManager* getUIManager();
		K_Engine::AudioManager* getAudioManager();
		K_Engine::InputManager* getInputManager();
		K_Engine::ComponentManager* getComponentManager();
		K_Engine::SceneManager* getSceneManager();

	private:
		std::string name;

		K_Engine::RenderManager* renderMan;
		K_Engine::PhysicsManager* physicsMan;
		//K_Engine::UIManager* uiMan;
		K_Engine::AudioManager* audioMan;
		K_Engine::InputManager* inputMan;
		K_Engine::ComponentManager* compMan;
		K_Engine::SceneManager* sceneMan;
		K_Engine::LogManager* logMan;

		HMODULE game;
		SceneLoad load;

		bool loadGame();

		// Debug section

		// THIS SHOULD BE DELETED EVENTUALLY UPON ENGINE RELEASE
		void debug();
	};
}
#endif // ENGINE_H