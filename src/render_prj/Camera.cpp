#include "Camera.h"

#include <OgreRoot.h>
#include <OgreSceneManager.h>
#include <OgreRenderWindow.h>
#include <OgreVector.h>
#include <OgreViewport.h>

#include <render_prj/RenderManager.h>

#include <input_prj/InputManager.h>

#include <utils_prj/checkML.h>

namespace K_Engine {
	Camera::Camera()
	{
		debugMovement = false;

		mCamera = K_Engine::RenderManager::GetInstance()->getSceneManager()->createCamera("K_Engine_Cam");
		mCamera->setAutoAspectRatio(true);

		mCameraNode = K_Engine::RenderManager::GetInstance()->getSceneManager()->getRootSceneNode()->createChildSceneNode();
		mCameraNode->setPosition(0, 0, 0);
		mCameraNode->lookAt(Ogre::Vector3(0, 0, -1), Ogre::Node::TS_PARENT);
		mCameraNode->attachObject(mCamera);

		Ogre::Viewport* vp = K_Engine::RenderManager::GetInstance()->getRenderWindow()->addViewport(mCamera);
		vp->setBackgroundColour(Ogre::ColourValue(0.5, 0.5, 0.5, 1.0));
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

	void Camera::setAnchor(Ogre::SceneNode* anchor)
	{
		mAnchorEntity = anchor;
	}

	void Camera::update()
	{
		debug();
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
		return { mCamera->getRealDirection().x, mCamera->getRealDirection().y, mCamera->getRealDirection().z };
	}

	void Camera::yaw(float angle)
	{
		mCameraNode->yaw(Ogre::Degree(angle));
	}

	void Camera::pitch(float angle)
	{
		mCameraNode->pitch(Ogre::Degree(angle));
	}

	void Camera::roll(float angle)
	{
		mCameraNode->roll(Ogre::Degree(angle));
	}

	void Camera::debug()
	{
		if (mAnchorEntity != nullptr && !debugMovement) mCameraNode->lookAt(mAnchorEntity->getPosition(), Ogre::Node::TS_PARENT);

		if (InputManager::GetInstance()->isKeyDown(K_Engine_Keycode::KEY_a)) yaw(-0.10);
		else if (InputManager::GetInstance()->isKeyDown(K_Engine_Keycode::KEY_d)) yaw(0.10);

		else if (InputManager::GetInstance()->isKeyDown(K_Engine_Keycode::KEY_s)) pitch(-0.10);
		else if (InputManager::GetInstance()->isKeyDown(K_Engine_Keycode::KEY_w)) pitch(0.10);

		else if (InputManager::GetInstance()->isKeyDown(K_Engine_Keycode::KEY_q)) roll(-0.10);
		else if (InputManager::GetInstance()->isKeyDown(K_Engine_Keycode::KEY_e)) roll(0.10);

		debugMovement = InputManager::GetInstance()->isKeyDown(K_Engine_Keycode::KEY_SPACE);
	}
}