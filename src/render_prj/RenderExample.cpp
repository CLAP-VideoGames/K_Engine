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

RenderExample::RenderExample()
{
	initRender();
	//loadResources();
	setupScenes();
	//initRTShaderSystem();
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

	mSDLWin = SDL_CreateWindow("Engine", 325, 200, 1280, 720, SDL_WINDOW_RESIZABLE);

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

	mRenderWin = mRoot->createRenderWindow("Anda", 1280, 720, false, &miscData);

	mRenderWin->setActive(true);
	mRenderWin->setVisible(true);
}

/// <summary>
/// Parsea el archivo resources.cfg para obtener las rutas de los recursos
/// </summary>
//void RenderExample::loadResources()
//{
//    Ogre::ConfigFile cf;
//    cf.load(mResourcesCfgPath);
//
//    Ogre::String name, locType;
//    Ogre::ConfigFile::SectionIterator secIt = cf.getSectionIterator();
//    while (secIt.hasMoreElements())
//    {
//        Ogre::ConfigFile::SettingsMultiMap* settings = secIt.getNext();
//        Ogre::ConfigFile::SettingsMultiMap::iterator it;
//        for (it = settings->begin(); it != settings->end(); ++it)
//        {
//            locType = it->first;
//            name = it->second;
//            Ogre::ResourceGroupManager::getSingleton().addResourceLocation(name, locType);
//        }
//    }
//}

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


/// <summary>
/// Crea la ventana inicial (cámara y viewport) y el manejador de escenas
/// </summary>
void RenderExample::setupScenes()
{
	mSceneMgr = mRoot->createSceneManager();

	mCameraNode = mSceneMgr->getRootSceneNode()->createChildSceneNode();
	mCameraNode->setPosition(0, 0, 80);
	mCameraNode->lookAt(Ogre::Vector3(0, 0, -300), Ogre::Node::TransformSpace::TS_WORLD);

	mCamera = mSceneMgr->createCamera("MainCam");
	mCamera->setNearClipDistance(5);

	mCameraNode->attachObject(mCamera);

	Ogre::Viewport* vp = mRenderWin->addViewport(mCamera);

	vp->setBackgroundColour(Ogre::ColourValue(0, 0, 0));

	mCamera->setAspectRatio(
		Ogre::Real(vp->getActualWidth()) /
		Ogre::Real(vp->getActualHeight()));

	Ogre::TextureManager::getSingleton().setDefaultNumMipmaps(5);
	Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();
}


/// <summary>
/// Actualiza la escena. True si lo hace correctamente, False si se cierra
/// </summary>
bool RenderExample::update()
{
	//Ogre::WindowEventUtilities::messagePump();

	if (mRenderWin->isClosed()) return false;

	if (!mRoot->renderOneFrame()) return false;

	return true;
}

void RenderExample::exampleScene()
{
	Ogre::Entity* ogreEntity = mSceneMgr->createEntity("ogrehead.mesh");

	Ogre::SceneNode* ogreNode = mSceneMgr->getRootSceneNode()->createChildSceneNode();
	ogreNode->attachObject(ogreEntity);

	mSceneMgr->setAmbientLight(Ogre::ColourValue(.5, .5, .5));

	Ogre::Light* light = mSceneMgr->createLight("MainLight");
	Ogre::SceneNode* lightNode = mSceneMgr->getRootSceneNode()->createChildSceneNode();
	lightNode->setPosition(20, 80, 50);
	lightNode->attachObject(light);
}