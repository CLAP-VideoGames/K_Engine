#include "Camera.h"

#include <render_prj/RenderManager.h>

#include <OgreRoot.h>
#include <OgreSceneManager.h>
#include <OgreRenderWindow.h>
#include <OgreVector.h>

KCamera::KCamera()
{
	mCamera = RenderManager::GetInstance()->getSceneManager()->createCamera("K_Engine_Cam");
	mCamera->setAutoAspectRatio(true);

	mCameraNode = RenderManager::GetInstance()->getSceneManager()->getRootSceneNode()->createChildSceneNode();
	mCameraNode->setPosition(0, 0, 0);
	mCameraNode->lookAt(Ogre::Vector3(0, 0, -1), Ogre::Node::TS_PARENT);
	mCameraNode->attachObject(mCamera);

	RenderManager::GetInstance()->getRenderWindow()->addViewport(mCamera);
}

KCamera::~KCamera() = default;

void KCamera::setNearClipDistance(float nClip)
{
	mCamera->setNearClipDistance(nClip);
}

void KCamera::setFarClipDistance(float fClip)
{
	mCamera->setFarClipDistance(fClip);
}

void KCamera::translateCamera(float x, float y, float z)
{
	mCameraNode->translate(x, y, z);
}

void KCamera::setCameraPos(float x, float y, float z)
{
	mCameraNode->setPosition(x, y, z);
}

void KCamera::rotateCamera(float pitchAngle = 0, float yawAngle = 0, float rollAngle = 0)
{
	if (pitchAngle != 0)
		pitch(pitchAngle);
	if (yawAngle != 0)
		yaw(yawAngle);
	if (rollAngle != 0)
		roll(rollAngle);
}

Ogre::Camera* KCamera::getCamera()
{
	return mCamera;
}

std::vector<float> KCamera::getCameraPosition()
{
	return { mCameraNode->getPosition().x, mCameraNode->getPosition().y, mCameraNode->getPosition().z };
}

std::vector<float> KCamera::getCameraDirection()
{
	return std::vector<float>();
}

void KCamera::yaw(float angle)
{
	mCameraNode->yaw(Ogre::Degree(angle));
}

void KCamera::pitch(float angle)
{
	mCameraNode->pitch(Ogre::Degree(angle));
}

void KCamera::roll(float angle)
{
	mCameraNode->roll(Ogre::Degree(angle));
}
