#pragma once
#ifndef ENTITY_H
#define ENTITY_H

#include <unordered_map>
#include <stdexcept>

#include <ecs_prj/ComponentManager.h>

class Component;

/*
*Our class Entity starts with only a Transform Component, which contains the rotation, position and scale of our entity
*You can alterate you entitys with the following methods
*/
class Entity
{

public:
	Entity();
	~Entity();

	//Template to get a Component
	template<typename T>
	T* getComponent() {
		std::string compName = getComponentName<T>();

		auto iterator = components.find(compName);

		if (iterator != components.end()) return static_cast<T*>(components[compName]);

		return nullptr;
	};

	//Template to remove a Component
	template<typename T>
	void removeComponent() {
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

	//Templete to check if an Entity has an specific component
	template <typename T>
	void hasComponent() {
		std::string compName = getComponentName<T>();

		auto iterator = components.find(compName);

		if (iterator != components.end()) return true;

		return false;
	}

	//Template to add any Component to our Entity
	template <typename T, typename ...Ts>
	T* addComponent(Ts &&... args) {
		std::string compName = getComponentName<T>();

		ComponentManager* comM = ComponentManager::GetInstance();

		T* c = comM->create<T>(this, args...);

		static_cast<Component*>(c)->awake();

		components.emplace(compName, c);

		return static_cast<T*>(c);
	}

	//This mehtos is used to set our Entity to active or unactive
	void setActive(bool a) { active = a; }

	//This methos updates our entity and is called once per frame
	void update();

	//To know when to destroy our entity
	bool destroyed() { return toDestroy; }

	//To know when to update our entity
	bool isActive() { return active; }

	//The start of everyComponent of our entity
	void start();

private:

	/*
	*We use this method to check that it is a Component what the user is introucing in our methods,
	*if it is not we throw an exception, if it is we return the componentName
	*/
	template<typename T>
	std::string getComponentName() {
		std::string compName;
		try {
			compName = T::GetId();
		}
		catch (std::string msg) {
			throw std::invalid_argument("There is no component with that name");
		}

		return compName;
	}

	bool active;    // determines if we update the entity or not
	bool toDestroy; // knows when do we have to erase an entity

	//Map to find our components and erase them using the id of the component
	std::unordered_map<std::string, Component*> components;

	//strings to give the entity a tag or a name
	std::string tag;
	std::string name;
};
#endif // ENTITY_H