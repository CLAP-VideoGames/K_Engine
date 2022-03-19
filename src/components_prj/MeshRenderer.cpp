#include "MeshRenderer.h"

#include <components_prj/Transform.h>

#include <ecs_prj/Entity.h>

#include <render_prj/RenderManager.h>
#include <utils_prj/CustomVector3.h>

#include <OgreEntity.h>
#include <OgreSceneNode.h>
#include <OgreSceneManager.h>
#include <OgreQuaternion.h>

std::string MeshRenderer::name = "MeshRenderer";

MeshRenderer::MeshRenderer(Entity* e) : Component("MeshRenderer", e) { 
}

MeshRenderer::~MeshRenderer() {}

void MeshRenderer::debug(){
	setSinbad();
	setMaterial("Ogre/Skin");
}

void MeshRenderer::start(){
	transformRf = entity->getComponent<Transform>();
	mNode->showBoundingBox(true);
}

void MeshRenderer::update(){
	syncScale();
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

Ogre::Quaternion MeshRenderer::EulerToQuaternion(CustomVector3 const& rot){
	Ogre::Matrix3 mx;
	mx.FromEulerAnglesYXZ(Ogre::Radian(rot.y), Ogre::Radian(rot.x), Ogre::Radian(rot.z));
	Ogre::Quaternion result(mx);
	return result;
}

void MeshRenderer::setSinbad()
{
	mEntity = RenderManager::GetInstance()->getSceneManager()->createEntity("cubeTest.mesh");
	mNode = RenderManager::GetInstance()->getSceneManager()->getRootSceneNode()->createChildSceneNode();
	mNode->attachObject(mEntity);
}

void MeshRenderer::syncScale() {
	transformRf = entity->getComponent<Transform>();
	CustomVector3 scaleT = transformRf->getScale();

	mNode->setScale(Ogre::Vector3(scaleT[0], scaleT[1], scaleT[2]));
}

void MeshRenderer::syncPosition(){
	CustomVector3 pos = transformRf->getPosition();
	mNode->setPosition(Ogre::Vector3(pos.x,pos.y, pos.z));
}

void MeshRenderer::syncRotation() {
	CustomVector3 rot = transformRf->getRotation();
	Ogre::Vector3 axis ={ Ogre::Real(rot.x), Ogre::Real(rot.y), Ogre::Real(rot.z) };
	Ogre::Quaternion q = EulerToQuaternion(rot);
	mNode->setOrientation(q);
}
