#include "RenderManager.h"

#include <iostream>
#include <string>
#ifndef _DEBUG
#include <windows.h>
#endif

#include <SDL.h>
#include <SDL_syswm.h>
#include <SDL_video.h>
#include <SDL_config_windows.h>

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

using namespace Ogre;
using namespace std;

std::unique_ptr<RenderManager> RenderManager::instance = nullptr;

RenderManager::RenderManager() = default;

RenderManager::~RenderManager() = default;

RenderManager* RenderManager::GetInstance() {
	return instance.get();
}

bool RenderManager::Init(std::string n) {
	try {
		instance.reset(new RenderManager());

		instance.get()->name = n;

		instance.get()->initRoot();
		instance.get()->initWindow();
		instance.get()->initResources();
		instance.get()->initScene();
		//initRTShaderSystem();
	}
	catch (const std::exception&) {
		return false;
	}

	return true;
}

bool RenderManager::Shutdown() {
	try {
		instance.get()->closeWindow();
		instance.get()->closeContext();

		instance.reset(nullptr);
	}
	catch (const std::exception&) {
		return false;
	}

	return true;
}

void RenderManager::render() {
	mRoot->renderOneFrame();
}

void RenderManager::exampleScene() {
	// finally something to render
	Ogre::Entity* ent = mSM->createEntity("ogrehead.mesh");
	Ogre::SceneNode* node = mSM->getRootSceneNode()->createChildSceneNode();
	float size = 0.2;
	node->setScale(size, size, size);
	node->attachObject(ent);
}

void RenderManager::initRoot()
{
	mRoot = new Ogre::Root("plugins.cfg", "ogre.cfg", "ogre.log");

	if (!mRoot->restoreConfig())
		mRoot->showConfigDialog(nullptr);

	mRoot->initialise(false);
}

/// <summary>
/// Inicializa la raiz
/// </summary>
void RenderManager::initWindow() {
	SDL_Init(SDL_INIT_EVERYTHING);

	int width = 1080, height = 720;
	Uint32 flags = SDL_WINDOW_RESIZABLE;
	mSDLWin = SDL_CreateWindow(name.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, flags);

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
	SDL_GetWindowWMInfo(mSDLWin, &wmInfo);

	Ogre::NameValuePairList miscData;
	miscData["externalWindowHandle"] = Ogre::StringConverter::toString(size_t(wmInfo.info.win.window));

	mRenderWin = mRoot->createRenderWindow(name.c_str(), width, height, false, &miscData);

	mRenderWin->setActive(true);
	mRenderWin->setVisible(true);

	SDL_SetWindowGrab(mSDLWin, SDL_bool(false));
	SDL_ShowCursor(true);
}

/// <summary>
/// Parsea el archivo resources.cfg para obtener las rutas de los recursos
/// </summary>
void RenderManager::initResources() {
	mFSLayer = new Ogre::FileSystemLayer(name);

	// load resource paths from config file
	Ogre::ConfigFile cf;

	std::string resourcesPath = mFSLayer->getConfigFilePath("resources.cfg");
	if (Ogre::FileSystemLayer::fileExists(resourcesPath))
		cf.load(resourcesPath);
	else {
		Ogre::ResourceGroupManager::getSingleton().addResourceLocation(Ogre::FileSystemLayer::resolveBundlePath("./assets"),
			"FileSystem", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);
	}

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

	//OgreAssert(!genLocs.empty(), ("Resource Group '" + sec + "' must contain at least one entry").c_str());

	Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();
}

/// <summary>
/// Crea la ventana inicial (cámara y viewport) y el manejador de escenas
/// </summary>
void RenderManager::initScene() {
	mSM = mRoot->createSceneManager();

	mSM->setAmbientLight(Ogre::ColourValue(.5, .5, .5));

	// without light we would just get a black screen    
	Ogre::Light* light = mSM->createLight("MainLight");
	Ogre::SceneNode* lightNode = mSM->getRootSceneNode()->createChildSceneNode();
	lightNode->setPosition(0, 10, 15);
	lightNode->attachObject(light);

	// also need to tell where we are
	Ogre::SceneNode* camNode = mSM->getRootSceneNode()->createChildSceneNode();
	camNode->setPosition(0, 0, 15);
	camNode->lookAt(Ogre::Vector3(0, 0, -1), Ogre::Node::TS_PARENT);

	// create the camera
	Ogre::Camera* cam = mSM->createCamera("myCam");
	cam->setNearClipDistance(5); // specific to this sample
	cam->setAutoAspectRatio(true);
	camNode->attachObject(cam);

	// and tell it to render into the main window
	mRenderWin->addViewport(cam);
}

void RenderManager::closeContext()
{
	mRoot->saveConfig();

	delete mFSLayer; mFSLayer = nullptr;
	delete mRoot; mRoot = nullptr;
}

void RenderManager::closeWindow()
{
	if (mRenderWin != nullptr) {
		mRoot->destroyRenderTarget(mRenderWin);
		mRenderWin = nullptr;
	}

	if (mSDLWin != nullptr) {
		SDL_DestroyWindow(mSDLWin);
		SDL_QuitSubSystem(SDL_INIT_VIDEO);
		mSDLWin = nullptr;
	}
}

/// <summary>
/// Inicia el sistema de shaders. El método debe llamarse despues de setupScenes
/// </summary>
void RenderManager::initRTShaderSystem()
{
	//if (Ogre::RTShader::ShaderGenerator::initialize())
	//{
	//    mShaderGenerator = Ogre::RTShader::ShaderGenerator::getSingletonPtr();

	//    // Create and register the material manager listener if it doesn't exist yet.
	//    if (!mMaterialMgrListener) {
	//        mMaterialMgrListener = new OgreBites::SGTechniqueResolverListener(mShaderGenerator);
	//        Ogre::MaterialManager::getSingleton().addListener(mMaterialMgrListener);
	//    }
	//}
	//mShaderGenerator->addSceneManager(mSceneMgr);
}

Ogre::Root* RenderManager::getRoot() {
	return mRoot;
}

Ogre::RenderTarget* RenderManager::getRenderWindow()
{
	return mRenderWin;
}
