#pragma once
#ifndef RENDERMANAGER_H
#define RENDERMANAGER_H

#include <string>
#include <memory>

namespace Ogre {
	class Root; 
	class Light;
	class Camera;
	class Viewport;
	class SceneNode;
	class RenderWindow;
	class SceneManager;
	class FileSystemLayer;
	class RenderTarget;
	class OverlaySystem;
	class OverlayManager;
}

class SDL_Window;

namespace K_Engine {
	class Camera;
	class Vector3;

	enum class LightType {
		POINT,
		DIRECTIONAL, 
		SPOTLIGHT
	};

	class  __declspec(dllexport) RenderManager {
	public:
		RenderManager();
		~RenderManager();

		static RenderManager* GetInstance();

		static bool Init(std::string n);
		static bool Shutdown();

		void locateResources();

		void render();

		// light creation methods
		void setAmbientLight(Vector3 light);
		Ogre::Light* createLight(LightType lType);

		Ogre::Root* getRoot();
		Ogre::SceneManager* getSceneManager();
		Ogre::RenderTarget* getRenderWindow();
		Camera* getCamera();

	private:
		static std::unique_ptr<RenderManager> instance;

		std::string name;

		Ogre::Root* mRoot;
		Ogre::SceneManager* mSM;

		SDL_Window* mSDLWin;
		Ogre::RenderWindow* mRenderWin;

		Camera* mCamera;

		void initRoot();
		void initWindow();
		void initScene();
		void preloadResources();

		void closeContext();
		void closeWindow();
	};
}
#endif // RENDERMANAGER_H