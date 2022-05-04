#include "Entity.h"

#include <ecs_prj/Component.h>

#include <utils_prj/Vector3.h>
#include <utils_prj/checkML.h>
#include <ecs_prj/EntityManager.h>

namespace K_Engine {
	Entity::Entity() {
		active = true;
		toDestroy = false;
		components = std::unordered_map<std::string, Component*>();
	}

	Entity::~Entity() {
		for (auto it = components.begin(); it != components.end(); ++it)
			delete it->second;
		components.clear();
	};

	void Entity::update(int frameTime)
	{
		auto it = components.begin();
		while ( it != components.end()) {
			//if it has to be destoyed, we destroy it
			if (it->second->destroyed()) {
				delete it->second;
				it = components.erase(it);
			}//If it is active, we update it
			//Update is called before physics update so the physics uses the information from the last update
			else { 
				if (it->second->enable) it->second->update(frameTime); 
				++it;
			}
		}

	}

	void Entity::fixedUpdate(int deltaTime)
	{
		auto it = components.begin();
		while (it != components.end()) {
			//if it has to be destoyed, we destroy it
			if (it->second->destroyed()) {
				delete it->second;
				it = components.erase(it);
			}//If it is active, we update it
			//Update is called before physics update so the physics uses the information from the last update
			else {
				if (it->second->enable) it->second->physicsUpdate(deltaTime);
				++it;
			}
		}
	}

	void Entity::awake()
	{
		for (auto e : components) e.second->awake();
	}

	void Entity::onEnable()
	{
		for (auto e : components) if(e.second->enable) e.second->onEnable();
	}

	void Entity::start() {
		for (auto e : components) 
			e.second->start();
	}

	void Entity::destroy()
	{
 		toDestroy = true;
	}

	void Entity::addChild(Entity* child) {
		children.push_back(child);
	}

	Component* Entity::addComponentByName(std::string name) {
		ComponentManager* comM = ComponentManager::GetInstance();
		
		Component* c = comM->createByName(name);

		//c.awake();

		components.emplace(name, c);

		return c;
	}

	void Entity::setActive(bool a)
	{
		active = a;
		for (auto e : components)
			e.second->setActive(a);
	}

}