#include "Camera.h"

#include <render_prj/RenderManager.h>

#include <OgreRoot.h>
#include <OgreSceneManager.h>
#include <OgreRenderWindow.h>
#include <OgreVector.h>

Camera::Camera()
{
	mCamera = RenderManager::GetInstance()->getSceneManager()->createCamera("K_Engine_Cam");

	mCameraNode = RenderManager::GetInstance()->getSceneManager()->getRootSceneNode()->createChildSceneNode();
	mCameraNode->setPosition(0, 0, 15);
	mCameraNode->lookAt(Ogre::Vector3(0, 0, -1), Ogre::Node::TS_PARENT);
	mCameraNode->attachObject(mCamera);
}

Camera::~Camera() = default;

void Camera::setNearClipDistance(float nClip)
{
	mCamera->setNearClipDistance(nClip);
}

void Camera::setFarClipDistance(float fClip)
{
	mCamera->setFarClipDistance(fClip);
}

void Camera::translateCamera(float x, float y, float z)
{
	mCameraNode->translate(x, y, z);
}

void Camera::setCameraPos(float x, float y, float z)
{
	mCameraNode->setPosition(x, y, z);
}

void Camera::rotateCamera(float pitchAngle = 0, float yawAngle = 0, float rollAngle = 0)
{
	if (pitchAngle != 0)
		pitch(pitchAngle);
	if (yawAngle != 0)
		yaw(yawAngle);
	if (rollAngle != 0)
		roll(rollAngle);
}

Ogre::Camera* Camera::getCamera()
{
	return mCamera;
}

std::vector<float> Camera::getCameraPosition()
{
	return { mCameraNode->getPosition().x, mCameraNode->getPosition().y, mCameraNode->getPosition().z };
}

std::vector<float> Camera::getCameraDirection()
{
	return std::vector<float>();
}
