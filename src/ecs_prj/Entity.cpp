#include "Entity.h"

Entity::Entity()
{
	active = true;
}

Entity::~Entity()
{

}

Component* Entity:: getComponent(string id_) {
	components.find(id_);
}
