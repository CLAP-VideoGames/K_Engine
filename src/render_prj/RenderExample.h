#ifndef RENDEREXAMPLE_H
#define RENDEREXAMPLE_H

#include <Ogre.h>

using namespace Ogre;

class SDL_Window;

class RenderExample
{
public:
	RenderExample();
	~RenderExample() {};

	bool update();
	void exampleScene();

private:
	Ogre::Root* mRoot;

	SDL_Window* mSDLWin;
	Ogre::RenderWindow* mRenderWin;

	Ogre::SceneManager* mSceneMgr;

	Ogre::Camera* mCamera;
	Ogre::SceneNode* mCameraNode;

	void initRender();
	void loadResources();
	void initRTShaderSystem();
	void setupScenes();
};
#endif // RENDEREXAMPLE_H