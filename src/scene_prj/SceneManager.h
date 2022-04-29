#pragma once
#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H

#include <string>
#include <stack>
#include <memory>

namespace K_Engine {
	class Scene;

	class  __declspec(dllexport) SceneManager {
	public:
		SceneManager();
		~SceneManager();

		static SceneManager* GetInstance();

		static bool Init();
		static bool Shutdown();

		//Allows the user to pop the scenes stack
		void popScene();

		//Allows the user to push a new scene into the stack
		void pushScene(Scene* newS);

		// Pops the actual scene and pushes the new scene
		void changeScene(Scene* newS);

		// Allows the user to pop the scenes stack
		void popSceneStr(std::string scene);

		// Pops the actual scene and pushes the new scene by string name
		void pushScenebyStr(std::string scene);

		// Pops the actual scene and pushes the new scene by string name
		void changeSceneStr(std::string scene);
		
		// called once per frame, it calls the actual scene update, requires time between frames
		void updateScene(int frameTime);

		// called once per frame, it calls the actual scene fixed update, requires fixed deltaTime
		void fixedUpdateScene(int deltaTime);

		// returns the top of the scene stack
		Scene* currentScene();

	private:
		static std::unique_ptr<SceneManager> instance;

		std::stack<Scene*> scenes;
	};
}
#endif