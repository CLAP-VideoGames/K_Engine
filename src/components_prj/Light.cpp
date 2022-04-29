#include "Light.h"

#include <OgreLight.h>
#include <OgreSceneNode.h>
#include <OgreSceneManager.h>

#include <render_prj/RenderManager.h>

#include <ecs_prj/Entity.h>

#include <components_prj/Transform.h>

#include <utils_prj/K_Map.h>
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

	Light::~Light() {
		delete diffuse; delete lookAt;
	}

	void Light::init(K_Map* information) {
		type = (LightType)information->valueToNumber("lightType");
		visible = information->valueToBool("visible");

		lookAt = information->valueToVector3("lookAt");
		diffuse = information->valueToVector3("diffuse");

		if (type == LightType::SPOTLIGHT)
			setSpotlightParameters(information->valueToNumber("innerAngle"), information->valueToNumber("outerAngle"));
	}

	void Light::start() {
		transformRf_ = entity->getComponent<Transform>();

		mLight = RenderManager::GetInstance()->createLight(type);
		mLight->setDiffuseColour(diffuse->x, diffuse->y, diffuse->z);
		//mLight->setSpecularColour(1, 0, 0);
		//mLight->setCastShadows(true);

		mNode = K_Engine::RenderManager::GetInstance()->getSceneManager()->getRootSceneNode()->createChildSceneNode();
		mNode->attachObject(mLight);
		mNode->setPosition(transformRf_->getPosition().x, transformRf_->getPosition().y, transformRf_->getPosition().z);
		mNode->lookAt(Ogre::Vector3((double)lookAt->x, (double)lookAt->y, (double)lookAt->z), Ogre::Node::TransformSpace::TS_WORLD);

		float ambient = 0.1;
		K_Engine::RenderManager::GetInstance()->setAmbientLight({ ambient, ambient, ambient });
	}

	void Light::changeType(LightType newType)
	{
		type = newType;
		mLight->setType((Ogre::Light::LightTypes)type);

		if (type == LightType::SPOTLIGHT)
			setSpotlightParameters(innerAngle, outerAngle);
	}

	void K_Engine::Light::changeDiffuse(Vector3 newDiff) {
		diffuse->x = newDiff.x; diffuse->y = newDiff.y; diffuse->z = newDiff.z;
		mLight->setDiffuseColour(newDiff.x, newDiff.y, newDiff.z);
	}

	void Light::setVisible(bool visib) {
		visible = visib;
		mLight->setVisible(visible);
	}

	bool Light::isVisible() {
		return visible;
	}

	void Light::setSpotlightParameters(float inAng, float outAng) {
		innerAngle = inAng; outerAngle = outAng;
		mLight->setSpotlightInnerAngle(Ogre::Radian(Ogre::Degree(inAng)));
		mLight->setSpotlightOuterAngle(Ogre::Radian(Ogre::Degree(outAng)));
	}
}