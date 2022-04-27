#pragma once
#ifndef SCENE_H
#define SCENE_H

#include <string>

namespace K_Engine {
	class EntityManager;
	class ScriptManager;

	class  __declspec(dllexport) Scene {
	public:
		//Creates the entityManager of our scene
		Scene();

		//Deletes the entityManager of our scene
		virtual ~Scene();

		//Init is called once when the Scene is created, use this method to load your lua map
		virtual void init(std::string nameMap);

		//Update is called once per frame
		void update(int frameTime);

		//Update is called once per frame
		void fixedUpdate(int deltaTime);

	protected:

		//In charge of keeping track of the entities of the scene
		EntityManager* entMan;
		ScriptManager* scriptMan;

		bool loadScene(std::string nameMap);
	};
}
#endif