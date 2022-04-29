#include "MeshRenderer.h"

#include <iostream>

#include <OgreEntity.h>
#include <OgreSceneNode.h>
#include <OgreSceneManager.h>
#include <OgreQuaternion.h>

#include <components_prj/Transform.h>

#include <ecs_prj/Entity.h>

#include <render_prj/RenderManager.h>
#include <render_prj/Camera.h>

#include <components_prj/Transform.h>

#include <utils_prj/Vector3.h>
#include <utils_prj/checkML.h>
#include <utils_prj/K_Map.h>

namespace K_Engine {
	std::string MeshRenderer::name = "MeshRenderer";

	MeshRenderer::MeshRenderer() : Component() {
		mNode = K_Engine::RenderManager::GetInstance()->getSceneManager()->getRootSceneNode()->createChildSceneNode();
	}

	MeshRenderer::MeshRenderer(Entity* e) : Component(e) {
		mNode = K_Engine::RenderManager::GetInstance()->getSceneManager()->getRootSceneNode()->createChildSceneNode();
	}

	MeshRenderer::~MeshRenderer() = default;

	std::string MeshRenderer::GetId() {
		return name;
	}

	void MeshRenderer::debug() {
		Ogre::AnimationStateSet* aux = mEntity->getAllAnimationStates();
		if (aux != nullptr) {
			for(auto it = aux->getAnimationStateIterator().begin(); it != aux->getAnimationStateIterator().end(); ++it) {
				std::string anim = it->first;
				std::cout << anim.c_str() << "\n";
			}
		}
	}

	void MeshRenderer::start() {
		transformRf = entity->getComponent<Transform>();
		mNode->showBoundingBox(true);
		syncScale();
	}

	void MeshRenderer::init(K_Map* information){
		setMesh(meshFile = information->value("MeshFile"));

		if (information->hasValue("Material")) 
			setMaterial(information->value("Material"));
	}

	void MeshRenderer::update(int frameTime) {
		syncPosition();
		syncRotation();
	}

	void MeshRenderer::onDisable() {
		setVisible(false);
	}

	void MeshRenderer::setVisible(bool value) {
		visible = value;
	}

	void MeshRenderer::setMaterial(std::string nMaterial) {
		if (nMaterial != material) {
			mEntity->setMaterialName(nMaterial);
			material = nMaterial;
		}
	}

	void MeshRenderer::setMesh(std::string mesh) {
		if (mNode) {
			mNode->detachAllObjects();
			mEntity = K_Engine::RenderManager::GetInstance()->getSceneManager()->createEntity(mesh);
			mNode->attachObject(mEntity);
		}
	}

	Ogre::SceneNode* MeshRenderer::getOgreNode()
	{
		return mNode;
	}

	Ogre::Entity* MeshRenderer::getOgreEntity()
	{
		return mEntity;
	}

	Ogre::Quaternion MeshRenderer::EulerToQuaternion(Vector3 const& rot) {
		Ogre::Matrix3 mx;
		mx.FromEulerAnglesYXZ(Ogre::Radian(rot.y), Ogre::Radian(rot.x), Ogre::Radian(rot.z));
		Ogre::Quaternion result(mx);
		return result;
	}

	void MeshRenderer::setSinbad() {
		if (mNode) {
			mEntity = K_Engine::RenderManager::GetInstance()->getSceneManager()->createEntity("ogrehead.mesh");
			mNode->attachObject(mEntity);
		}
	}

	void MeshRenderer::syncScale() {
		transformRf = entity->getComponent<Transform>();
		Vector3 scaleT = transformRf->getScale();

		//mNode->scale();
		mNode->setScale(Ogre::Vector3(scaleT[0], scaleT[1], scaleT[2]));
	}

	void MeshRenderer::syncPosition() {
		Vector3 pos = transformRf->getPosition();
		mNode->setPosition(Ogre::Vector3(pos.x, pos.y, pos.z));
	}

	void MeshRenderer::syncRotation() {
		Vector3 rot = transformRf->getRotation();
		Ogre::Vector3 axis = { Ogre::Real(rot.x), Ogre::Real(rot.y), Ogre::Real(rot.z) };
		Ogre::Quaternion q = EulerToQuaternion(rot);
		mNode->setOrientation(q);
	}
}