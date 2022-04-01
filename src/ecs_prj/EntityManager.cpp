#include "EntityManager.h"

#include <ecs_prj/Entity.h>

namespace K_Engine {
	EntityManager::EntityManager() = default;

	EntityManager::~EntityManager()
	{
		while (!entities.empty()) {
			delete entities[0];
			entities.erase(entities.begin());
		}
	}

	Entity* EntityManager::addEntity()
	{
		auto c = new Entity();

		entities.push_back(c);

		return c;
	}

	void EntityManager::update(int frameTime)
	{
		//The basic cycle of every entity
		for (int i = 0; i < entities.size(); i++) {
			auto e = entities[i];
			//if it has to be destoyed, we destroy it
			if (e->destroyed()) {
				delete e;
				entities.erase(entities.begin() + i);
			}//If it is active, we update it
			else if (e->isActive())e->update(frameTime);
		}
	}

	void EntityManager::fixedUpdate(int deltaTime)
	{
		//The same as above but for physics
		for (int i = 0; i < entities.size(); i++) {
			auto e = entities[i];
			//if it has to be destoyed, we destroy it
			if (e->destroyed()) {
				delete e;
				entities.erase(entities.begin() + i);
			}//If it is active, we update its physics
			else if (e->isActive())e->fixedUpdate(deltaTime);
		}
	}

	void EntityManager::start()
	{
		for (auto e : entities) e->start();
	}
}