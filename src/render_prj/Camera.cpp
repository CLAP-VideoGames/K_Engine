#include "Camera.h"


Camera::Camera(RenderManager* r)
{
	rendM = r;
	mSM = r->getSceneManager();
	cam = r->getSceneManager()->createCamera("myCam");
	cam->setNearClipDistance(5); // specific to this sample
	cam->setAutoAspectRatio(true);
	mCamNode->attachObject(cam);
}