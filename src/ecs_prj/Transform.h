#pragma once
#include "Component.h"
#include <vector>

namespace Ogre {
	class SceneNode;
}

class Transform : public Component
{
public:
	Transform();
	~Transform();

	static std::string GetId();

	void translate(float x, float y, float z);
	void rotate(float x, float y, float z);
	void scale(float x, float y, float z);

	Ogre::SceneNode* getNode();

private:
	static std::string name;

	Ogre::SceneNode* mNode;
};