#include "Transform.h"

#include <render_prj/RenderManager.h>

#include <OgreSceneManager.h>

std::string Transform::name = "Transform";

Transform::Transform() : Component("Transform", nullptr)
{
	mNode = RenderManager::GetInstance()->getSceneManager()->getRootSceneNode()->createChildSceneNode();
}

Transform::~Transform()
{
	delete mNode; mNode = nullptr;
}

std::string Transform::GetId()
{
	return name;
}

void Transform::translate(float x, float y, float z)
{
	mNode->translate(x, y, z, Ogre::Node::TS_WORLD);
}

void Transform::rotate(float x, float y, float z)
{
	Ogre::Matrix3 rotMatrix;
	rotMatrix.FromEulerAnglesXYZ(Ogre::Degree(x), Ogre::Degree(y), Ogre::Degree(z));
	Ogre::Quaternion rotQuat(rotMatrix);
	mNode->setOrientation(rotQuat);
}

void Transform::scale(float x, float y, float z)
{
	mNode->scale(x, y, z);
}

Ogre::SceneNode* Transform::getNode()
{
	return mNode;
}
