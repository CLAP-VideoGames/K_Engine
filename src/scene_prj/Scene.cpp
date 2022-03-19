#include "Scene.h"
#include "ecs_prj/EntityManager.h"

Scene::Scene()
{
	entMan = new EntityManager();
}

Scene::~Scene()
{
	delete entMan;
}
