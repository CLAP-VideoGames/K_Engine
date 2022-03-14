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
	for (auto c : components) 
		c.second->update();
}
