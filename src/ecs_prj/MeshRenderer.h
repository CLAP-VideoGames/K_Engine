#pragma once
#include "Component.h"

namespace Ogre {
	class Node;
	class Entity;
}

class MeshRenderer : public Component
{
public:

	MeshRenderer();
	~MeshRenderer();

	//Required method for the component name
	static std::string GetId() { return name; }

	void setVisible(bool value);

	void setMaterial(std::string nMaterial);

protected:


private:

	//Required
	static std::string name;

	//Reference to object's entity
	Ogre::Entity* ogreEntity = nullptr;

	//Reference to the object's node
	Ogre::Node* ogreNode = nullptr;

	//Bool to control if the object is visible or not (default true)
	bool visible = true;

	//Name of the object's material
	std::string material;
};