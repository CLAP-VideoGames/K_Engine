#include "Light.h"

#include <render_prj/RenderManager.h>
#include <ecs_prj/Entity.h>

#include <OgreLight.h>
#include <OgreSceneNode.h>
#include <OgreSceneManager.h>

namespace K_Engine {
	//Required
	std::string Light::name = "Light";

	Light::Light(Entity* e) : Component("Light", e) {
		name = id;
	}

	Light::Light(Entity* e, LightType lType, bool enable) : Component("Light", e) {
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

		mLight->setDiffuseColour(0, 1, 1);
		mLight->setSpecularColour(1, 0, 0);
		mLight->setCastShadows(true);

		if (type == LightType::SPOTLIGHT) {
			mLight->setSpotlightInnerAngle(Ogre::Radian(Ogre::Degree(0)));
			mLight->setSpotlightOuterAngle(Ogre::Radian(Ogre::Degree(40)));
		}
	}

	void Light::setVisible(bool visib) {
		visible = visib;
		mLight->setVisible(visible);
	}

	bool Light::isVisible() {
		return visible;
	}
}