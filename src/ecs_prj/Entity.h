#pragma once
#include <unordered_map>
#include "Component.h"

using namespace std;

class Entity
{
public:
	Entity();
	~Entity();

	Component* getComponent(string id_);

	void setActive(bool a) { active = false; }
private:

	//bool to determine if we update the entity or not
	bool active;

	//Map to find our components and erase them using the id of the component
	unordered_map<string, Component>components;


	//addComponent(Component c){
	//}

	//remove component(Component c){		
	//}
};