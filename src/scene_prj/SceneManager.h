#pragma once
#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H

#include <string>
#include <stack>
#include <memory>

namespace K_Engine {
	class Scene;

	class SceneManager {
	public:
		SceneManager();
		~SceneManager();

		static SceneManager* GetInstance();

		static bool Init(std::string n);
		static bool Shutdown();

		//Allows the user to pop the scenes stack
		void popScene();

		//Allows the user to push a new scene into the stack
		void pushScene(Scene* newS);

		/// <summary>
		/// Pops the actual scene and pushes the new scene
		/// </summary>
		/// <param name="newS"></param>
		void changeScene(Scene* newS);

		/// <summary>
		/// called once per frame, it calls the actual scene update
		/// </summary>
		void updateScene();

		/// <summary>
		/// called once per frame, it calls the actual scene fixed update
		/// </summary>
		void fixedUpdateScene();

		/// <summary>
		/// returns the top of the scene stack
		/// </summary>
		/// <returns></returns>
		Scene* currentScene();

	private:
		static std::unique_ptr<SceneManager> instance;

		std::string name;

		std::stack<Scene*> scenes;
	};
}
#endif