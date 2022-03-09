#include "Entity.h"
#include <stdexcept>
#include <Component.h>

Entity::Entity()
{
	active = true;
	toDestroy = false;

	//Podemos hacer un new Transform desde aqui directamente
}

Entity::~Entity()
{

}

void Entity::update()
{
	for (auto c : components) {
		c.second->update();
	}
}

template<typename T>
Component* Entity::getComponent()
{
	std::string compName = getComponentName<T>();

	auto iterator = components.find(compName);
		
	if (iterator != components.end()) return components[compName];

	return nullptr;															
}

template<typename T>
void Entity::removeComponent()
{
	std::string compName = getComponentName<T>();

	auto iterator = components.find(compName);

	//If the entity has the component we remove it
	if (hasComponent<T>()) {		
		auto it = components.find(compName);

		components.erase(it);

		delete components[compName];

		components[compName] = nullptr;
	}

}

template<typename T>
void Entity::hasComponent()
{
	std::string compName = getComponentName<T>();

	auto iterator = components.find(compName);

	if (iterator != components.end()) return true;

	return false;
}

template<typename T>
Component* Entity::addComponent()
{
	std::string componentName = getComponentName<T>();

	if (hasComponent<T>()) {
		return components[componentName];
	}

}

template<typename T>
std::string Entity::getComponentName()
{
	std::string compName;
	try {

		compName = T::GetId();
	}
	catch (std::string msg) {
		throw std::invalid_argument("There is no component with that name");
	}

	return compName;
}
