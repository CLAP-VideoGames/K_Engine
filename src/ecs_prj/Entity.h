#ifndef ENTITY_H
#define ENTITY_H
#include <unordered_map>
#include "Component.h"

class Entity
{
public:
	Entity();
	~Entity();

	template<typename T>
	Component* getComponent();

	template<typename T>
	void removeComponent();

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