#ifndef ENTITY_H
#define ENTITY_H
#include <unordered_map>
#include "Component.h"

class Entity
{
public:
	Entity();
	~Entity();

	Component* getComponent(std::string id_);

	void setActive(bool a) { active = false; }
private:

	//bool to determine if we update the entity or not
	bool active;

	//Map to find our components and erase them using the id of the component
	std::unordered_map<std::string, Component>components;

	//Map to find our components by number
	std::unordered_map<int, Component>components;


	//addComponent(Component c){
	//}

	//remove component(Component c){		
	//}
};
#endif