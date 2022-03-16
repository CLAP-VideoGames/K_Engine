#include "Entity.h"

#include <ecs_prj/Component.h>

Entity::Entity()
{
	active = true;
	toDestroy = false;

	//Podemos hacer un new Transform desde aqui directamente
}

Entity::~Entity() { }

void Entity::update()
{
	for (auto c : components) {
		//Update is called before physics update so the physics uses the information from the last update
		c.second->update();

		c.second->physicsUpdate();
	}
}

void Entity::start()
{
	for (auto e : components) {
		e.second->start();
	}
}
