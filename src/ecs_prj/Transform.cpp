#include "Transform.h"

//Required
std::string Transform::name = "Transform";

Transform::Transform(Ogre::SceneNode* mNode_) : Component("Transform")
{
	mNode = mNode_;
	name = id;
}

Transform::~Transform()
{

}
