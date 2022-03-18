#pragma once
#ifndef CAMERA_H_
#define CAMERA_H_

#include <memory>
#include <vector>

namespace Ogre {
	class Root;
	class Camera;
	class SceneNode;
	class SceneManager;
	class Viewport;
}

class Camera {
public:
	Camera();
	~Camera();

	void setNearClipDistance(float nClip);
	void setFarClipDistance(float fClip);

	void translateCamera(float x, float y, float z);
	void setCameraPos(float x, float y, float z);

	void rotateCamera(float pitchAngle, float yawAngle, float rollAngle);

	Ogre::Camera* getCamera();
	std::vector<float> getCameraPosition();
	std::vector<float> getCameraDirection();

private:
	Ogre::Camera* mCamera;
	Ogre::SceneNode* mCameraNode;
	Ogre::Viewport* mViewport;

	void yaw(float angle);		// Rotate in Y axis 
	void pitch(float angle);	// Rotate in X axis
	void roll(float angle);		// Rotate in Z axis
};
#endif // CAMERA_H_

