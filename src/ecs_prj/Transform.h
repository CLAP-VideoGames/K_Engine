#pragma once
#include "Component.h"
#include <vector>

namespace Ogre {
	class SceneNode;
}

class Transform : public Component
{
public:

	Transform(Ogre::SceneNode* mNode);
	~Transform();

	//Required method for the component name
	static std::string GetId() { return name; }

protected:

	
private:

	//Required
	static std::string name;

	//Position, scale and rotation with their default initialization
	Ogre::SceneNode* mNode;

};