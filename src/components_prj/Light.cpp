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

	Light::Light() : Component() {

	}

	Light::Light(Entity* e) : Component(e) {
	}

	Light::Light(Entity* e, LightType lType, bool enable) : Component( e) {
		type = lType;
		visible = enable;
	}

	Light::~Light() = default;

	std::string Light::GetId() {
		return name;
	}

	void Light::start() {
		mLight = RenderManager::GetInstance()->createLight(type);
		mNode = K_Engine::RenderManager::GetInstance()->getSceneManager()->getRootSceneNode()->createChildSceneNode();
		mNode->attachObject(mLight);
		mNode->setPosition(0, 5, 0);
		mNode->lookAt({ 0, -3, 0 }, Ogre::Node::TransformSpace::TS_WORLD);

		diffuse = Vector3(1, 1, 1);
		mLight->setDiffuseColour(diffuse.x, diffuse.y, diffuse.z);
		mLight->setSpecularColour(1, 0, 0);
		//mLight->setCastShadows(true);

		if (type == LightType::SPOTLIGHT)
			setSpotlightParameters(0, 45);

		K_Engine::RenderManager::GetInstance()->setAmbientLight({ 0.3, 0.3, 0.3 });
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