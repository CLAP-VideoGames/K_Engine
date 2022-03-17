#include "Camera.h"


Camara::Camara(RenderManager* r)
{
	rendM = r;
	mSM_ = rendM->getSceneManager();

	mCameraNode = mSM_->getRootSceneNode()->createChildSceneNode();
	mCameraNode->setPosition(0, 0, 15);
	mCameraNode->lookAt(Ogre::Vector3(0, 0, -1), Ogre::Node::TS_PARENT);

	near = 5;
	far = 10000;
	mRoot = r->getRoot();
	mCamera = mSM_->createCamera("myCam");
	mCamera->setNearClipDistance(near);
	mCamera->setFarClipDistance(far);
	mCamera->setAutoAspectRatio(true);
	mCameraNode->attachObject(mCamera);

	rendM->getRenderWindow()->addViewport(mCamera);
}

void Camara::moveCamera(float x, float y, float z)
{
	mCameraNode->translate(x, y, z);
}


void Camara::setCamPos(float x, float y, float z)
{
	mCameraNode->setPosition(x, y, z);
}

void Camara::rotateCamera()
{
	//mCameraNode->yaw, roll, pitch 
	//mCameraNode->rotate()
}

Ogre::Camera* Camara::getCam()
{
	return mCamera;
}
Ogre::Viewport* Camara::getViewPort()
{
	return vp;
}