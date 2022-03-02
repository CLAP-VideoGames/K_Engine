#ifndef RENDEREXAMPLE_H
#define RENDEREXAMPLE_H

#include <Ogre.h>

using namespace Ogre;

class RenderExample
{
public:
	RenderExample();
	~RenderExample() {};

	void initRoot();
	bool update();
	void exampleScene();

private:
	Ogre::Root* mRoot;
	Ogre::String mResourcesCfgPath;
	Ogre::String mPluginsCfgPath;

	Ogre::RenderWindow* mWindow;
	Ogre::SceneManager* mSceneMgr;

	Ogre::Camera* mCamera;
	Ogre::SceneNode* mCameraNode;

	//Ogre::RTShader::ShaderGenerator* mShaderGenerator;
	//Ogre::MaterialManager::Listener* mMaterialMgrListener;

	void loadResources();
	void initRTShaderSystem();
	void setupScenes();
};
#endif // RENDEREXAMPLE_H