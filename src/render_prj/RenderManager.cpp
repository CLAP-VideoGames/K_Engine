#include "RenderManager.h"

#include <iostream>
#include <string>

#define SDL_MAIN_HANDLED
#include <SDL.h>
#include <SDL_syswm.h>
#include <SDL_video.h>
#include <SDL_config_windows.h>

#include <windows.h>

#include <OgreRoot.h>
#include <OgreEntity.h>
#include <OgreCamera.h>
#include <OgreString.h>
#include <OgreViewport.h>
#include <OgreConfigFile.h>
#include <OgreRenderWindow.h>
#include <OgreSceneManager.h>
#include <OgreTextureManager.h>
#include <OgreFileSystemLayer.h>
#include <OgreGpuProgramManager.h>
#include <OgreLogManager.h>

#include <OgreOverlaySystem.h>
#include <OgreOverlayManager.h>

#include <render_prj/Camera.h>

#include <log_prj/LogManager.h>

#include <utils_prj/Vector3.h>
#include <utils_prj/checkML.h>

using namespace Ogre;
using namespace std;

namespace K_Engine {
	std::unique_ptr<RenderManager> RenderManager::instance = nullptr;

	RenderManager::RenderManager() = default;

	RenderManager::~RenderManager() = default;

	RenderManager* RenderManager::GetInstance() {
		return instance.get();
	}

	bool RenderManager::Init(std::string n) {
		try {
			instance.reset(new RenderManager());

			instance.get()->initRoot();
			instance.get()->initWindow(n);
			instance.get()->initScene();
		}
		catch (Ogre::Exception& e) {
			return K_Engine::LogManager::GetInstance()->addLog(K_Engine::LogType::FATAL, e.getFullDescription());
		}

		return K_Engine::LogManager::GetInstance()->addLog(K_Engine::LogType::INFO, "Render manager initialization success");
	}

	bool RenderManager::Shutdown() {
		try {
			instance.get()->closeWindow();
			instance.get()->closeContext();

			instance.reset(nullptr);
		}
		catch (Ogre::Exception& e) {
			return K_Engine::LogManager::GetInstance()->addLog(K_Engine::LogType::FATAL, e.getFullDescription());
		}

		return K_Engine::LogManager::GetInstance()->addLog(K_Engine::LogType::INFO, "Render manager shutdown success");
	}


	/// <summary>
	/// Parsea el archivo resources.cfg para obtener las rutas de los recursos
	/// </summary>
	void RenderManager::locateResources(std::string file) {
		// load resource paths from config file
		Ogre::ConfigFile cf;

		if (Ogre::FileSystemLayer::fileExists(file))
			cf.load(file);
		else
			Ogre::ResourceGroupManager::getSingleton().addResourceLocation(Ogre::FileSystemLayer::resolveBundlePath("./assets"),
				"FileSystem", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);

		// go through all specified resource groups
		std::string sec, type, arch;
		Ogre::ConfigFile::SettingsBySection_::const_iterator seci;
		for (seci = cf.getSettingsBySection().begin(); seci != cf.getSettingsBySection().end(); ++seci) {
			sec = seci->first;
			const Ogre::ConfigFile::SettingsMultiMap& settings = seci->second;
			Ogre::ConfigFile::SettingsMultiMap::const_iterator i;

			// go through all resource paths
			for (i = settings.begin(); i != settings.end(); i++) {
				type = i->first;
				arch = Ogre::FileSystemLayer::resolveBundlePath(i->second);
				Ogre::ResourceGroupManager::getSingleton().addResourceLocation(arch, type, sec);
			}
		}

		sec = Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME;
		const Ogre::ResourceGroupManager::LocationList genLocs = Ogre::ResourceGroupManager::getSingleton().getResourceLocationList(sec);

		Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();
	}

	void RenderManager::render() {
		mCamera->update();
		mRoot->renderOneFrame();
	}

	void RenderManager::setFullScreen() {
		fullScreen = !fullScreen;

		actual_window_width = default_window_width, actual_window_height = default_window_height;
		if (fullScreen) {
			RECT rect; HWND hd = GetDesktopWindow();
			GetClientRect(hd, &rect);

			/*double dpi = 1; int zoom = GetDpiForWindow(hd);
			switch (zoom) {
			case 120: dpi = 1.25; break;
			case 144: dpi = 1.5; break;
			case 192: dpi = 2; break;
			default: break;
			}*/

			actual_window_width = (rect.right - rect.left);
			actual_window_height = (rect.bottom - rect.top);
		}

		Uint32 flags = fullScreen ? SDL_WINDOW_FULLSCREEN_DESKTOP : SDL_WINDOW_RESIZABLE;
		SDL_SetWindowSize(mSDLWin, actual_window_width, actual_window_height);
		SDL_SetWindowFullscreen(mSDLWin, flags);
		mRenderWin->windowMovedOrResized();
	}

	void RenderManager::exitWindow() {
		SDL_Event quit; quit.type = SDL_QUIT;
		SDL_PushEvent(&quit);
	}

	void RenderManager::setAmbientLight(Vector3 light) {
		mSM->setAmbientLight(Ogre::ColourValue(light.x, light.y, light.z));
	}

	Ogre::Light* RenderManager::createLight(LightType lType) {
		return mSM->createLight((Ogre::Light::LightTypes)lType);
	}

	void RenderManager::initRoot() {
		mRoot = new Ogre::Root("plugins.cfg", "ogre.cfg", "ogre.log");

		if (!mRoot->restoreConfig())
			mRoot->showConfigDialog(nullptr);

		mRoot->initialise(false);
	}

	/// <summary>
	/// Inicializa la raiz
	/// </summary>
	void RenderManager::initWindow(std::string n) {
		name = n;

		if (SDL_Init(SDL_INIT_EVERYTHING))
			throw SDL_GetError();

		fullScreen = false;
		resetWindowSize();
		Uint32 flags = SDL_WINDOW_RESIZABLE;
		mSDLWin = SDL_CreateWindow(name.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, default_window_width, default_window_height, flags);
		if (!mSDLWin)
			throw Ogre::Exception(Ogre::Exception::ERR_INTERNAL_ERROR, SDL_GetError(), "SDL Window not loaded correctly");

		// make background screen black so my eyes don't bleed
		SDL_Renderer* renderer = SDL_CreateRenderer(mSDLWin, -1, 0);
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderClear(renderer);
		SDL_RenderPresent(renderer);
		SDL_DestroyRenderer(renderer);

		/**
		* Get driver-specific information about a window.
		*
		* You must include SDL_syswm.h for the declaration of SDL_SysWMinfo.
		*
		* The caller must initialize the `info` structure's version by using
		* `SDL_VERSION(&info.version)`, and then this function will fill in the rest
		* of the structure with information about the given window.
		*
		* \param window the window about which information is being requested
		* \param info an SDL_SysWMinfo structure filled in with window information
		* \returns SDL_TRUE if the function is implemented and the `version` member
		*          of the `info` struct is valid, or SDL_FALSE if the information
		*          could not be retrieved; call SDL_GetError() for more information.
		*
		* \since This function is available since SDL 2.0.0.
		*/
		SDL_SysWMinfo wmInfo;
		SDL_GetVersion(&wmInfo.version);
		if (!SDL_GetWindowWMInfo(mSDLWin, &wmInfo))
			throw Ogre::Exception(Ogre::Exception::ERR_INTERNAL_ERROR, SDL_GetError(), "RenderManager");

		Ogre::NameValuePairList miscData;
		miscData["externalWindowHandle"] = Ogre::StringConverter::toString(size_t(wmInfo.info.win.window));

		mRenderWin = mRoot->createRenderWindow(name.c_str(), default_window_width, default_window_height, false, &miscData);

		mRenderWin->setActive(true);
		mRenderWin->setVisible(true);

		SDL_SetWindowGrab(mSDLWin, SDL_bool(false));
		SDL_ShowCursor(true);
	}

	/// <summary>
	/// Crea la ventana inicial (cámara y viewport) y el manejador de escenas
	/// </summary>
	void RenderManager::initScene() {
		mSM = mRoot->createSceneManager();
		mSM->setAmbientLight(Ogre::ColourValue(.5, .5, .5));

		// We create a camera and assign it to a viewport
		mCamera = new Camera();
		mCamera->setNearClipDistance(1);
		mCamera->setFarClipDistance(10000);
		mCamera->setCameraPos(-4, 10, 10);
	}

	void RenderManager::closeContext() {
		mRoot->saveConfig();

		delete mCamera; mCamera = nullptr;
		delete mRoot; mRoot = nullptr;
	}

	void RenderManager::closeWindow() {
		if (mRenderWin != nullptr) {
			mRoot->destroyRenderTarget(mRenderWin);
			mRenderWin = nullptr;
		}

		if (mSDLWin != nullptr) {
			SDL_DestroyWindow(mSDLWin);
			SDL_QuitSubSystem(SDL_INIT_VIDEO);
			mSDLWin = nullptr;
		}

		SDL_Quit();
	}

	void RenderManager::resetWindowSize() {
		SDL_DisplayMode info; SDL_GetDesktopDisplayMode(0, &info);
		actual_window_width = default_window_width = info.w / 1.5; 
		actual_window_height = default_window_height = info.h / 1.5;
	}

	Ogre::Root* RenderManager::getRoot() {
		return mRoot;
	}

	Ogre::SceneManager* RenderManager::getSceneManager() {
		return mSM;
	}

	Ogre::RenderTarget* RenderManager::getRenderWindow() {
		return mRenderWin;
	}

	Camera* RenderManager::getCamera() {
		return mCamera;
	}

	int RenderManager::windowHeight() {
		return actual_window_height;
	}

	int RenderManager::windowWidth() {
		return actual_window_width;
	}
}