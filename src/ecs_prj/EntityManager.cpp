#include "EntityManager.h"

#include <ecs_prj/Entity.h>

#include <utils_prj/checkML.h>

namespace K_Engine {
	EntityManager::EntityManager() = default;

	EntityManager::~EntityManager()
	{
		while (!entities.empty()) {
			delete entities[0];
			entities.erase(entities.begin());
		}
	}

	Entity* EntityManager::addEntity(bool inExecution)
	{
		auto c = new Entity();

		c->setMan(this);

		if (inExecution)toStart.push_back(c);
		else entities.push_back(c);

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

		for (auto a : toStart) {
			a->start();
			entities.push_back(a);
		}

		toStart.clear();
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

	void EntityManager::awake()
	{
		for (auto e : entities) e->awake();
	}

	void EntityManager::onEnable()
	{
		for (auto e : entities) e->onEnable();
	}

	void EntityManager::start(){
		for (auto e : entities) e->start();
	}

	void EntityManager::hideElements() {
		for (auto e : entities) {
			e->setActive(false);
		}
	}
	void EntityManager::showElements()
	{
		for (auto e : entities) {
			e->setActive(true);
		}
	}
	void EntityManager::destroyEntity(Entity* e)
	{
		auto it = entities.begin();
		while (it != entities.end() && *it != e) ++it;
		if (it != entities.end()) {
			delete e;
			entities.erase(it);
		}

	}
}