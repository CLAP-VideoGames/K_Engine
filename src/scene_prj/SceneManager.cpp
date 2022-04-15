#include "SceneManager.h"

#include <scene_prj/Scene.h>

#include <utils_prj/checkML.h>

namespace K_Engine {
	std::unique_ptr<SceneManager> SceneManager::instance = nullptr;

	SceneManager::SceneManager() = default;

	SceneManager::~SceneManager() = default;

	SceneManager* SceneManager::GetInstance() {
		return instance.get();
	}

	bool SceneManager::Init(std::string n) {
		instance.reset(new SceneManager());

		instance.get()->name = n;

		return true;
	}

	bool SceneManager::Shutdown()
	{
		while (!instance.get()->scenes.empty()) {
			delete instance.get()->scenes.top();
			instance.get()->scenes.pop();
		}

		instance.reset(nullptr);

		return true;
	}

	void SceneManager::popScene()
	{
		scenes.pop();
	}

	void SceneManager::pushScene(Scene* newS)
	{
		scenes.push(newS);
	}

	void SceneManager::changeScene(Scene* newS)
	{
		popScene();
		pushScene(newS);
	}

	void SceneManager::updateScene(int frameTime)
	{
		scenes.top()->update(frameTime);
	}

	void SceneManager::fixedUpdateScene(int deltaTime)
	{
		scenes.top()->fixedUpdate(deltaTime);
	}

	Scene* SceneManager::currentScene()
	{
		return scenes.top();
	}
}