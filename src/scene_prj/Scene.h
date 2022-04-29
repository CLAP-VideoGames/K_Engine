#pragma once
#ifndef SCENE_H
#define SCENE_H

#include <string>

namespace K_Engine {
	class EntityManager;
	class ScriptManager;

	class  __declspec(dllexport) Scene {
	public:
		Scene();
		Scene(std::string sceneName);
		virtual ~Scene();

		// Init is called once when the Scene is created, use this method to load your lua map
		virtual void init(std::string nameMap);
		virtual void init();

		void update(int frameTime);      // Update is called once per frame
		void fixedUpdate(int deltaTime); // FixedUpdate is called 'x' times per frame

		void hideElements();
		void showElements();

		std::string getName();

	protected:
		std::string name;

		EntityManager* entMan;    // In charge of keeping track of the entities of the scene
		ScriptManager* scriptMan;

		bool loadScene(std::string nameMap);
	};
}
#endif