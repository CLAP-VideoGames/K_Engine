#pragma once
#include "Component.h"

namespace Ogre {
	class SceneNode;
	class Entity;
}

/*
* MeshRender is the component used to add diferent model to our entities
* It takes the information of the model position scale and rotation from transform
*/
class MeshRenderer : public Component
{
public:

	MeshRenderer();
	~MeshRenderer();

	//Required method for the component name
	static std::string GetId() { return name; }

	virtual void debug();

	void setVisible(bool value);

	void setMaterial(std::string nMaterial);
	
	//Debuggin method to know that our component works as intended
	void setSinbad();

	void scale();

protected:


private:

	//Required
	static std::string name;

	//Reference to object's entity
	Ogre::Entity* ogreEntity = nullptr;

	//Reference to the object's node
	Ogre::SceneNode* ogreNode = nullptr;

	//Bool to control if the object is visible or not (default true)
	bool visible = true;

	//Name of the object's material
	std::string material;
};