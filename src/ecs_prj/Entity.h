#pragma once
#ifndef ENTITY_H
#define ENTITY_H
#include <unordered_map>

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
	T* getComponent();

	//Template to remove a Component
	template<typename T>
	void removeComponent();

	//Templete to check if an Entity has an specific component
	template <typename T>
	void hasComponent();

	//Template to add any Component to our Entity
	template <typename T>
	T* addComponent();

	//This mehtos is used to set our Entity to active or unactive
	void setActive(bool a) { active = a; }

	//This methos updates our entity and is called once per frame
	void update();

	//To know when to destroy our entity
	bool destroyed() { return toDestroy; }

	//To know when to update our entity
	bool isActive() { return active; }

private:

	/*
	*We use this method to check that it is a Component what the user is introucing in our methods,
	*if it is not we throw an exception, if it is we return the componentName
	*/
	template<typename T>
	std::string getComponentName();

	//bool to determine if we update the entity or not
	bool active;
	//bool to know when do we have to erase an entity
	bool toDestroy;

	//Map to find our components and erase them using the id of the component
	std::unordered_map<std::string, Component*>components;
		
	//strings to give the entity a tag or a name
	std::string tag;
	std::string name;

};
#endif