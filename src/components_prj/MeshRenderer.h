#pragma once
#ifndef MESHRENDERER_H
#define MESHRENDERER_H
#include <ecs_prj/Component.h>

class Transform;

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
	MeshRenderer(Entity* e);
	~MeshRenderer();

	//Required method for the component name
	static std::string GetId() { return name; }

	virtual void debug();

	virtual void start();
	virtual void update();

	void setVisible(bool value);

	void setMaterial(std::string nMaterial);

private:
	void syncScale();
	
	void syncPosition();

	// required
	static std::string name;

	// reference to tranform Component
	Transform* transformRf;

	// reference to the object's node & entity
	Ogre::SceneNode* mNode;
	Ogre::Entity* mEntity;

	bool visible;		  // visibility of the object
	std::string material; // name of the object's material

	// debuggin method to know that our component works as intended
	void setSinbad();
};
#endif // MESHRENDERER_H