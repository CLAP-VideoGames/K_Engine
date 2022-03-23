#include "Scene.h"

#include <ecs_prj/EntityManager.h>

namespace K_Engine {
	Scene::Scene()
	{
		entMan = new EntityManager();
	}

	Scene::~Scene()
	{
		delete entMan;
	}

	void Scene::init() {};

	void Scene::update() {};
}
