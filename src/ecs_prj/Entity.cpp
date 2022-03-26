#include "Entity.h"

#include <ecs_prj/Component.h>
#include <components_prj/Transform.h>
#include <utils_prj/KVector3.h>

Entity::Entity()
{
	active = true;
	toDestroy = false;

	//Podemos hacer un new Transform desde aqui directamente
}

Entity::~Entity() = default;

void Entity::update()
{
	for (auto c : components) {
		//Update is called before physics update so the physics uses the information from the last update
		c.second->update();
	}

	//Update for the entity children
	for (auto c : children) {
		c->update();
	}
}

void Entity::fixedUpdate()
{
	for (auto c : components) {

		c.second->physicsUpdate();
	}

	//Update for the entity children
	for (auto c : children) {
		c->fixedUpdate();
	}
}

void Entity::start()
{
	for (auto e : components) {
		e.second->start();
	}
}

void Entity::addChild(Entity* child)
{
	children.push_back(child);
}
