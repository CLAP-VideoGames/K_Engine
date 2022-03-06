#ifndef RENDEREXAMPLE_H
#define RENDEREXAMPLE_H

#include <string>
#include <memory>

namespace Ogre {
	class Log;
	class Root;
	class Camera;
	class Viewport;
	class SceneNode;
	class LogManager;
	class RenderWindow;
	class SceneManager;
	class FileSystemLayer;
}

class SDL_Window;

class RenderManager {
public:
	RenderManager();
	~RenderManager();

	static RenderManager* getInstance();

	void init(std::string n);
	void render();
	void shutdown();

	void exampleScene();

private:
	static std::unique_ptr<RenderManager> instance;

	std::string name;

	Ogre::Root* mRoot;
	Ogre::SceneManager* mSM;
	Ogre::FileSystemLayer* mFSLayer;

	SDL_Window* mSDLWin;
	Ogre::RenderWindow* mRenderWin;

	Ogre::Camera* mCamera;
	Ogre::SceneNode* mCameraNode;

	void initRoot();
	void initWindow();
	void initResources();
	void initScene();
	void initRTShaderSystem();

	void closeContext();
	void closeWindow();

	Ogre::Root* getRoot();
};
#endif // RENDEREXAMPLE_H