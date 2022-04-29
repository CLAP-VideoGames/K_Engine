#include "Light.h"

#include <OgreLight.h>
#include <OgreSceneNode.h>
#include <OgreSceneManager.h>

#include <render_prj/RenderManager.h>

#include <ecs_prj/Entity.h>

#include <utils_prj/Vector3.h>
#include <utils_prj/checkML.h>

namespace K_Engine {
	//Required
	std::string Light::name = "Light";

	std::string Light::GetId() {
		return name;
	}

	Light::Light() : Component() {}

	Light::Light(Entity* e) : Component(e) {}

	Light::Light(Entity* e, LightType lType, bool enable) : Component( e) {
		type = lType;
		visible = enable;
	}

	Light::~Light() = default;

	void Light::start() {
		mLight = RenderManager::GetInstance()->createLight(type);
		mNode = K_Engine::RenderManager::GetInstance()->getSceneManager()->getRootSceneNode()->createChildSceneNode();
		mNode->attachObject(mLight);
		mNode->setPosition(0, 4.5, 0);
		mNode->lookAt({ 0, -1, -1 }, Ogre::Node::TransformSpace::TS_WORLD);

		float factorDiff = 2.5f;
		diffuse = Vector3(factorDiff, factorDiff, factorDiff);

		mLight->setDiffuseColour(diffuse.x, diffuse.y, diffuse.z);
		//mLight->setSpecularColour(1, 0, 0);
		//mLight->setCastShadows(true);

		if (type == LightType::SPOTLIGHT)
			setSpotlightParameters(0, 45);
		float ambient = 0.1;
		K_Engine::RenderManager::GetInstance()->setAmbientLight({ ambient, ambient, ambient });
	}

	void Light::changeType(LightType newType)
	{
		type = newType;
		mLight->setType((Ogre::Light::LightTypes)type);

		if (type == LightType::SPOTLIGHT)
			setSpotlightParameters(0, 45);
	}

	void K_Engine::Light::changeDiffuse(Vector3 newDiff)
	{
		mLight->setDiffuseColour(newDiff.x, newDiff.y, newDiff.z);
	}

	void K_Engine::Light::restoreDiffuse()
	{
		mLight->setDiffuseColour(diffuse.x, diffuse.y, diffuse.z);
	}

	void Light::setVisible(bool visib) {
		visible = visib;
		mLight->setVisible(visible);
	}

	bool Light::isVisible() {
		return visible;
	}

	void Light::setSpotlightParameters(float inAng, float outAng)
	{
		mLight->setSpotlightInnerAngle(Ogre::Radian(Ogre::Degree(inAng)));
		mLight->setSpotlightOuterAngle(Ogre::Radian(Ogre::Degree(outAng)));
	}
}