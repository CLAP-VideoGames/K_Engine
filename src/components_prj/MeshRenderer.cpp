#include "MeshRenderer.h"

#include <components_prj/Transform.h>

#include <ecs_prj/Entity.h>

#include <render_prj/RenderManager.h>
#include <utils_prj/KVector3.h>

#include <OgreEntity.h>
#include <OgreSceneNode.h>
#include <OgreSceneManager.h>
#include <OgreQuaternion.h>

std::string MeshRenderer::name = "MeshRenderer";

MeshRenderer::MeshRenderer(Entity* e) : Component("MeshRenderer", e) { 
	mNode = RenderManager::GetInstance()->getSceneManager()->getRootSceneNode()->createChildSceneNode();
}

MeshRenderer::~MeshRenderer() {}

void MeshRenderer::debug(){
	setSinbad();
	setMaterial("Ogre/Skin");
}

void MeshRenderer::start(){
	transformRf = entity->getComponent<Transform>();
	mNode->showBoundingBox(true);
	syncDimensions();
}

void MeshRenderer::update(){
	syncPosition();
	syncRotation();
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

void MeshRenderer::setMesh(std::string mesh){
	if (mNode) {
		mNode->detachAllObjects();
		mEntity = RenderManager::GetInstance()->getSceneManager()->createEntity(mesh);
		mNode->attachObject(mEntity);
	}
}

Ogre::Quaternion MeshRenderer::EulerToQuaternion(KVector3 const& rot){
	Ogre::Matrix3 mx;
	mx.FromEulerAnglesYXZ(Ogre::Radian(rot.y), Ogre::Radian(rot.x), Ogre::Radian(rot.z));
	Ogre::Quaternion result(mx);
	return result;
}

void MeshRenderer::setSinbad(){
	if(mNode){
		mEntity = RenderManager::GetInstance()->getSceneManager()->createEntity("ogrehead.mesh");
		mNode->attachObject(mEntity);
	}
}

void MeshRenderer::syncScale() {
	transformRf = entity->getComponent<Transform>();
	KVector3 scaleT = transformRf->getScale();

	mNode->scale(Ogre::Vector3(scaleT[0], scaleT[1], scaleT[2]));
}

void MeshRenderer::syncDimensions(){
	transformRf = entity->getComponent<Transform>();
	KVector3 scaleT = transformRf->getDimensions();

	mNode->setScale(Ogre::Vector3(scaleT[0], scaleT[1], scaleT[2]));
}

void MeshRenderer::syncPosition(){
	KVector3 pos = transformRf->getPosition();
	mNode->setPosition(Ogre::Vector3(pos.x,pos.y, pos.z));
}

void MeshRenderer::syncRotation() {
	KVector3 rot = transformRf->getRotation();
	Ogre::Vector3 axis ={ Ogre::Real(rot.x), Ogre::Real(rot.y), Ogre::Real(rot.z) };
	Ogre::Quaternion q = EulerToQuaternion(rot);
	mNode->setOrientation(q);
}
