#ifndef ENTITY_H
#define ENTITY_H
#include <unordered_map>
#include "Component.h"

class Entity
{
public:
	Entity();
	~Entity();

	//In this three methods(getComponent, removeComponent and hasComponent) we try to execute T::getId() so we know if the user used a Component
	//If it didnt we throw an exception saying that Component that does not exist 

	//Template to get a Component
	template<typename T>
	Component* getComponent();

	//Template to remove a Component
	template<typename T>
	void removeComponent();

	//Templete to check if an Entity has an specific component
	template <typename T>
	void hasComponent();

	void setActive(bool a) { active = a; }
private:

	//bool to determine if we update the entity or not
	bool active;
	//bool to know when do we have to erase an entity
	bool toDestroy;

	//Map to find our components and erase them using the id of the component
	std::unordered_map<std::string, Component*>components;
		
	//strings to give the entity a tag or a name
	std::string tag;
	std::string name;

	//addComponent(Component c){
	//}

	//remove component(Component c){		
	//}
};
#endif