#include "SceneManager.h"

#include <scene_prj/Scene.h>

#include <log_prj/LogManager.h>

#include <utils_prj/checkML.h>

namespace K_Engine {
	std::unique_ptr<SceneManager> SceneManager::instance = nullptr;

	SceneManager::SceneManager() = default;

	SceneManager::~SceneManager() = default;

	SceneManager* SceneManager::GetInstance() {
		return instance.get();
	}

	bool SceneManager::Init() {
		try {
			instance.reset(new SceneManager());
		}
		catch (const std::exception& e) {
			return K_Engine::LogManager::GetInstance()->addLog(K_Engine::LogType::FATAL, e.what());
		}

		return K_Engine::LogManager::GetInstance()->addLog(K_Engine::LogType::INFO, "Scene manager initialization success");
	}

	bool SceneManager::Shutdown()
	{
		try {
			while (!instance.get()->scenes.empty()) {
				delete instance.get()->scenes.top();
				instance.get()->scenes.pop();
			}

			instance.reset(nullptr);
		}
		catch (const std::exception& e) {
			return K_Engine::LogManager::GetInstance()->addLog(K_Engine::LogType::FATAL, e.what());
		}

		return K_Engine::LogManager::GetInstance()->addLog(K_Engine::LogType::INFO, "Scene manager shutdown success");
	}

	void SceneManager::popScene() {
		if (scenes.size() < 2)
			return;

		scenes.top()->hideElements();
		scenes.pop();
	}

	void SceneManager::pushScene(Scene* newS) {
		scenes.push(newS);
	}

	void SceneManager::changeScene(Scene* newS) {
		popScene();
		pushScene(newS);
	}

	void SceneManager::startScene(std::string scene) {
		pushSceneStr(scene);
	}

	void SceneManager::popSceneStr(std::string scene) {
		if (scenes.size() < 2)
			return;

		while (scenes.top()->getName() != scene)
			popScene();

		if (scenes.empty())
			K_Engine::LogManager::GetInstance()->addLog(K_Engine::LogType::FATAL, "Scene name not found");
		else
			scenes.top()->showElements();
	}
	
	void SceneManager::pushSceneStr(std::string scene) {
		if (!scenes.empty())
			scenes.top()->hideElements();

		Scene* exampleScene = new Scene(scene);
		exampleScene->init();
		pushScene(exampleScene);
	}

	void SceneManager::changeSceneStr(std::string scene) {
		popScene();
		pushSceneStr(scene);
	}

	void SceneManager::updateScene(int frameTime) {
		scenes.top()->update(frameTime);
	}

	void SceneManager::fixedUpdateScene(int deltaTime) {
		scenes.top()->fixedUpdate(deltaTime);
	}

	Scene* SceneManager::currentScene() {
		return scenes.top();
	}
}