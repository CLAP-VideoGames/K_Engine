#include "RenderExample.h"

#include <iostream>

#include <SDL.h>
#include <SDL_syswm.h>
#include <SDL_video.h>
#include <SDL_config_windows.h>

#include <OgreRoot.h>
#include <OgreEntity.h>
#include <OgreCamera.h>
#include <OgreViewport.h>
#include <OgreConfigFile.h>
#include <OgreRenderWindow.h>
#include <OgreSceneManager.h>
#include <OgreTextureManager.h>
#include <OgreFileSystemLayer.h>
#include <OgreGpuProgramManager.h>

#include <string>

using namespace Ogre;

RenderExample::RenderExample() {
	initRender();

	locateResources();
	loadResources();

	setupScenes();
	exampleScene();
	//initRTShaderSystem();
}

RenderExample::~RenderExample(){
	mRoot->saveConfig();

	shutdown();

	delete mRoot;
	mRoot = nullptr;
}

void RenderExample::shutdown() { 
	if (mRenderWin != nullptr){
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
/// Inicializa la raiz
/// </summary>
void RenderExample::initRender() {
	SDL_Init(SDL_INIT_EVERYTHING);

	mRoot = new Ogre::Root("plugins.cfg", "ogre.cfg", "ogre.log");

	if (!mRoot->restoreConfig())
		mRoot->showConfigDialog(nullptr);

	mRoot->initialise(false);

	int width = 1080;
	int height = 720;
	Uint32 flags = SDL_WINDOW_RESIZABLE;
	std::string name = "K Engine";
	mSDLWin = SDL_CreateWindow(name.c_str() , SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, flags);

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

	mSM = mRoot->createSceneManager();
	mFSLayer = new Ogre::FileSystemLayer(name);
}

void RenderExample::setCamNLight(){

}

/// <summary>
/// Parsea el archivo resources.cfg para obtener las rutas de los recursos
/// </summary>
void RenderExample::loadResources() {
	Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();
}

void RenderExample::locateResources(){
	// load resource paths from config file
	Ogre::ConfigFile cf;

	Ogre::String resourcesPath = mFSLayer->getConfigFilePath("resources.cfg");
	if (Ogre::FileSystemLayer::fileExists(resourcesPath))
	{
		cf.load(resourcesPath);
	}
	else
	{
		//Ogre::ResourceGroupManager::getSingleton().addResourceLocation(
		//	Ogre::FileSystemLayer::resolveBundlePath(mSolutionPath + "\\media"),
		//	"FileSystem", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);
	}

	Ogre::String sec, type, arch;
	// go through all specified resource groups
	Ogre::ConfigFile::SettingsBySection_::const_iterator seci;
	for (seci = cf.getSettingsBySection().begin(); seci != cf.getSettingsBySection().end(); ++seci) {
		sec = seci->first;
		const Ogre::ConfigFile::SettingsMultiMap& settings = seci->second;
		Ogre::ConfigFile::SettingsMultiMap::const_iterator i;

		// go through all resource paths
		for (i = settings.begin(); i != settings.end(); i++)
		{
			type = i->first;
			arch = Ogre::FileSystemLayer::resolveBundlePath(i->second);
			Ogre::ResourceGroupManager::getSingleton().addResourceLocation(arch, type, sec);
		}
	}

	sec = Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME;
	const Ogre::ResourceGroupManager::LocationList genLocs = Ogre::ResourceGroupManager::getSingleton().getResourceLocationList(sec);

	//OgreAssert(!genLocs.empty(), ("Resource Group '" + sec + "' must contain at least one entry").c_str());

	arch = genLocs.front().archive->getName();
	type = genLocs.front().archive->getType();

	// Add locations for supported shader languages
	if (Ogre::GpuProgramManager::getSingleton().isSyntaxSupported("glsles"))
	{
		Ogre::ResourceGroupManager::getSingleton().addResourceLocation(arch + "/materials/programs/GLSLES", type, sec);
	}
	else if (Ogre::GpuProgramManager::getSingleton().isSyntaxSupported("glsl"))
	{
		Ogre::ResourceGroupManager::getSingleton().addResourceLocation(arch + "/materials/programs/GLSL120", type, sec);

		if (Ogre::GpuProgramManager::getSingleton().isSyntaxSupported("glsl150"))
		{
			Ogre::ResourceGroupManager::getSingleton().addResourceLocation(arch + "/materials/programs/GLSL150", type, sec);
		}
		else
		{
			Ogre::ResourceGroupManager::getSingleton().addResourceLocation(arch + "/materials/programs/GLSL", type, sec);
		}

		if (Ogre::GpuProgramManager::getSingleton().isSyntaxSupported("glsl400"))
		{
			Ogre::ResourceGroupManager::getSingleton().addResourceLocation(arch + "/materials/programs/GLSL400", type, sec);
		}
	}
	else if (Ogre::GpuProgramManager::getSingleton().isSyntaxSupported("hlsl"))
	{
		Ogre::ResourceGroupManager::getSingleton().addResourceLocation(arch + "/materials/programs/HLSL", type, sec);
	}

	/*mRTShaderLibPath = arch + "/RTShaderLib";
	Ogre::ResourceGroupManager::getSingleton().addResourceLocation(mRTShaderLibPath + "/materials", type, sec);

	if (Ogre::GpuProgramManager::getSingleton().isSyntaxSupported("glsles"))
	{
		Ogre::ResourceGroupManager::getSingleton().addResourceLocation(mRTShaderLibPath + "/GLSL", type, sec);
		Ogre::ResourceGroupManager::getSingleton().addResourceLocation(mRTShaderLibPath + "/GLSLES", type, sec);
	}
	else if (Ogre::GpuProgramManager::getSingleton().isSyntaxSupported("glsl"))
	{
		Ogre::ResourceGroupManager::getSingleton().addResourceLocation(mRTShaderLibPath + "/GLSL", type, sec);
	}
	else if (Ogre::GpuProgramManager::getSingleton().isSyntaxSupported("hlsl"))
	{
		Ogre::ResourceGroupManager::getSingleton().addResourceLocation(mRTShaderLibPath + "/HLSL", type, sec);
	}*/
}

/// <summary>
/// Inicia el sistema de shaders. El método debe llamarse despues de setupScenes
/// </summary>
void RenderExample::initRTShaderSystem()
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

void RenderExample::render() {
	mRoot->renderOneFrame();
}

/// <summary>
/// Crea la ventana inicial (cámara y viewport) y el manejador de escenas
/// </summary>
void RenderExample::setupScenes() {
	//mCamera = mSM->createCamera("myCam");
	//mCamera->setNearClipDistance(5);
	//mCamera->setAutoAspectRatio(true);

	//mCameraNode = mSM->getRootSceneNode()->createChildSceneNode();
	//mCameraNode->attachObject(mCamera);
	//mCameraNode->setPosition(0, 0, 140);
	////mCameraNode->lookAt(Ogre::Vector3(0, 0, 0), Ogre::Node::TransformSpace::TS_WORLD);

	//Ogre::Viewport* vp = mRenderWin->addViewport(mCamera);

	//vp->setBackgroundColour(Ogre::ColourValue(0.7, 0.8, 0.9));

	//mCamera->setAspectRatio(
	//	Ogre::Real(vp->getActualWidth()) /
	//	Ogre::Real(vp->getActualHeight()));

	//Ogre::TextureManager::getSingleton().setDefaultNumMipmaps(5);
	//Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();
}


/// <summary>
/// Actualiza la escena. True si lo hace correctamente, False si se cierra
/// </summary>
bool RenderExample::update() {
	//Ogre::WindowEventUtilities::messagePump();

	if (mRenderWin->isClosed()) return false;

	if (!mRoot->renderOneFrame()) return false;

	return true;
}

void RenderExample::exampleScene() {
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

	// finally something to render
	Ogre::Entity* ent = mSM->createEntity("ogrehead.mesh");
	Ogre::SceneNode* node = mSM->getRootSceneNode()->createChildSceneNode();
	float size = 0.1;
	node->setScale(size, size, size);
	node->attachObject(ent);

}

Ogre::Root* RenderExample::getRoot(){
	return mRoot;
}
