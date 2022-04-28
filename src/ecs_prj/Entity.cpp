#include "Entity.h"

#include <ecs_prj/Component.h>

#include <utils_prj/Vector3.h>
#include <utils_prj/checkML.h>

namespace K_Engine {
	Entity::Entity() {
		active = true;
		toDestroy = false;
	}

	Entity::~Entity() {
		for (auto it = components.begin(); it != components.end(); ++it)
			delete it->second;
		components.clear();
	};

	void Entity::update(int frameTime)
	{
		for (auto c : components)
			//Update is called before physics update so the physics uses the information from the last update
			c.second->update(frameTime);

		//Update for the entity children
		for (auto c : children)
			c->update(frameTime);
	}

	void Entity::fixedUpdate(int deltaTime)
	{
		for (auto c : components)
			c.second->physicsUpdate(deltaTime);

		//Update for the entity children
		for (auto c : children) 
			c->fixedUpdate(deltaTime);
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

	void Entity::addChild(Entity* child) {
		children.push_back(child);
	}

	Component* Entity::addComponentByName(std::string name) {
		ComponentManager* comM = ComponentManager::GetInstance();
		
		Component* c = comM->createByName(name);

		//c->awake();

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