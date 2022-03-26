#pragma once
#ifndef ENGINE_H
#define ENGINE_H

#include <string>

namespace K_Engine {
	class RenderManager;
	class PhysicsManager;
	class UIManager;
	class AudioManager;
	class InputManager;
	class ComponentManager;
	class SceneManager;

	class Engine
	{
	public:
		Engine(std::string n);
		~Engine();

		bool init();
		void setup();
		void run();
		bool shutdown();

	private:
		std::string name;

		K_Engine::RenderManager* renderMan;
		K_Engine::PhysicsManager* physicsMan;
		K_Engine::UIManager* uiMan;
		K_Engine::AudioManager* audioMan;
		K_Engine::InputManager* inputMan;
		K_Engine::ComponentManager* compMan;
		K_Engine::SceneManager* sceneMan;

		// Debug section

		// THIS SHOULD BE DELETED EVENTUALLY UPON ENGINE RELEASE
		void debug();
	};
}

#endif // ENGINE_H