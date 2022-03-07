#include "Entity.h"
#include <stdexcept>

Entity::Entity()
{
	active = true;
	toDestroy = false;
}

Entity::~Entity()
{

}

template<typename T>
Component* Entity::getComponent()
{
	std::string compName;
	try {

		compName = T::getId();
	}
	catch(std::string msg) {
		throw std::invalid_argument("There is no component with that name");
	}

	auto iterator = components.find(compName);
		
	if (iterator != components.end()) return components[compName];

	return nullptr;															
}

template<typename T>
void Entity::removeComponent()
{
	std::string compName;
	try {
		compName = T::getId();
	}
	catch(std::string msg) {
		throw std::invalid_argument("There is no component with that name");
	}

	auto iterator = components.find(compName);

	if (hasComponent<T>()) {		
		auto it = components.find(compName);

		components.erase(it);
	}

	delete components[compName];

	components[compName] = nullptr;
}

template<typename T>
void Entity::hasComponent()
{
	std::string compName;

	try {
		compName = T::getId();
	}
	catch(std::string msg) {
		throw std::invalid_argument("There is no component with that name");
	}

	auto iterator = components.find(compName);

	if (iterator != components.end()) return true;

	return false;
}
