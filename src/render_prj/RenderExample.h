#ifndef RENDEREXAMPLE_H
#define RENDEREXAMPLE_H

namespace Ogre {
	class Root;
	class RenderWindow;
	class Camera;
	class SceneManager;
	class Viewport;
	class SceneNode;
	class FileSystemLayer;
	class Log;
	class LogManager;
}

class SDL_Window;

class RenderExample {
public:
	RenderExample();
	~RenderExample();

	bool update();
	void exampleScene();
	void render();


	Ogre::Root* getRoot();

private:
	Ogre::Root* mRoot;

	SDL_Window* mSDLWin;
	Ogre::RenderWindow* mRenderWin;

	Ogre::SceneManager* mSM;
	Ogre::FileSystemLayer* mFSLayer;
	Ogre::Camera* mCamera;
	Ogre::SceneNode* mCameraNode;

	void shutdown();

	void initRender();
	void loadResources();
	void locateResources();
	void setCamNLight();

	void initRTShaderSystem();
	void setupScenes();
};
#endif // RENDEREXAMPLE_H