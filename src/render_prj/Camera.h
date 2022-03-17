#pragma once
#ifndef _CAMERA_H_
#define _CAMERA_H_
#include <memory>
#include "RenderManager.h"
#include <OgreRoot.h>
#include <OgreRenderWindow.h>

class Camara
{
private:

	RenderManager* rendM = nullptr;

	float near, far; // How near or far is the camera looking 
	
	Ogre::SceneManager* mSM_ = nullptr;
	Ogre::Camera* mCamera = nullptr;
	Ogre::SceneNode* mCameraNode = nullptr;
	Ogre::Root* mRoot;
	Ogre::Viewport* vp = nullptr;

public:
	Camara(RenderManager* r);
	~Camara() {};

	Ogre::Camera* getCam();
	Ogre::Viewport* getViewPort();


	void moveCamera(float x, float y, float z);
	void setCamPos(float x, float y, float z);
	void rotateCamera();
	

};
#endif _CAMERA_H_

