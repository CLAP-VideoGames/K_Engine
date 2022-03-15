#pragma once
#include "RenderManager.h"


class Camera
{
public:
	Camera(RenderManager* r);
	~Camera() {};

private:

	RenderManager* rendM;

	float near, far; // How near or far is the camera looking

	Ogre::SceneManager* mSM;
	Ogre::SceneNode* mCamNode;
	Ogre::Viewport* vp;
	Ogre::Camera* cam;



};

