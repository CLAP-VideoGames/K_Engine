#pragma once
#ifndef RENDERMANAGER_H
#define RENDERMANAGER_H

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
	class RenderTarget;
}

class SDL_Window;

class RenderManager {
public:
	RenderManager();
	~RenderManager();

	static RenderManager* GetInstance();

	static bool Init(std::string n);
	static bool Shutdown();

	void render();

	void exampleScene();

	Ogre::Root* getRoot();
	Ogre::SceneManager* getSceneManager();
	Ogre::RenderTarget* getRenderWindow();

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
};
#endif // RENDERMANAGER_H