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
	class RenderTarget;
}

class SDL_Window;

namespace K_Engine {
	class Camera;
	class Vector3;

	enum class __declspec(dllexport) LightType {
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

		void locateResources(std::string file);

		void render();

		// window related methods
		void setFullScreen();
		void exitWindow();

		// light creation methods
		void setAmbientLight(Vector3 light);
		Ogre::Light* createLight(LightType lType);

		Camera* getCamera();
		Ogre::Root* getRoot();
		Ogre::SceneManager* getSceneManager();
		Ogre::RenderTarget* getRenderWindow();

		int windowHeight();
		int windowWidth();
		
	private:
		static std::unique_ptr<RenderManager> instance;

		std::string name;

		Ogre::Root* mRoot;
		Ogre::SceneManager* mSM;

		SDL_Window* mSDLWin;
		Ogre::RenderWindow* mRenderWin;

		Camera* mCamera;

		int window_height, window_width;
		bool fullScreen;

		void initRoot();
		void initWindow(std::string n);
		void initScene();

		void closeContext();
		void closeWindow();
	};
}
#endif // RENDERMANAGER_H