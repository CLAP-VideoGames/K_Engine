#include "SceneManager.h"
#include "Scene.h"

SceneManager::SceneManager() = default;

SceneManager::~SceneManager()
{
	while (!scenes.empty())
	{
		delete scenes.top();
		scenes.pop();
	}
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

void SceneManager::updateScene()
{
	scenes.top()->update();
}

Scene* SceneManager::actualSecne()
{
	return scenes.top();
}
