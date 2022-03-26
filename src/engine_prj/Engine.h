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

	// THIS SHOULD DELETED, PERIOD (when we develop the SceneManager)
	class EntityManager;
	class Transform;

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

		// Debug section
		
		// THIS SHOULD DELETED, PERIOD (when we develop the SceneManager)
		K_Engine::EntityManager* entMan;
		K_Engine::Transform* t;

		// THIS SHOULD BE DELETED EVENTUALLY UPON ENGINE RELEASE
		void debug();
	};
}

#endif // ENGINE_H