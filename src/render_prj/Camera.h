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

namespace K_Engine {

	class KCamera {
	public:
		KCamera();
		~KCamera();

		// Sets the distance to the near clipping plane.
		void setNearClipDistance(float nClip);

		// Sets the distance to the far clipping plane.
		void setFarClipDistance(float fClip);

		// Moves the camera from its original position
		void translateCamera(float x, float y, float z);

		// Set the position of the camera
		void setCameraPos(float x, float y, float z);

		// Rotate the camera to a certain direction, depending on the angle it receives
		void rotateCamera(float pitchAngle, float yawAngle, float rollAngle);

		// Returns the object Camera
		Ogre::Camera* getCamera();

		// Returns the position of the camera
		std::vector<float> getCameraPosition();

		// Returns the direction the camera is looking at
		std::vector<float> getCameraDirection();

	private:
		Ogre::Camera* mCamera;
		Ogre::SceneNode* mCameraNode;
		Ogre::Viewport* mViewport;

		void yaw(float angle);		// Rotate in Y axis 
		void pitch(float angle);	// Rotate in X axis
		void roll(float angle);		// Rotate in Z axis
	};
}
#endif // CAMERA_H_

