#include "MeshRenderer.h"

#include <ecs_prj/Transform.h>
#include <ecs_prj/Entity.h>

#include <render_prj/RenderManager.h>
#include <utils_prj/CustomVector3.h>

#include <OgreEntity.h>
#include <OgreSceneNode.h>
#include <OgreSceneManager.h>

std::string MeshRenderer::name = "MeshRenderer";

MeshRenderer::MeshRenderer(Entity* e) : Component("MeshRenderer", e) { 
	transformRf = entity->getComponent<Transform>();
}

MeshRenderer::~MeshRenderer() {}

void MeshRenderer::debug()
{
	setSinbad();
	setMaterial("Ogre/Skin");
}

void MeshRenderer::update(){
	syncPosition();
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

void MeshRenderer::setSinbad()
{
	mEntity = RenderManager::GetInstance()->getSceneManager()->createEntity("ogrehead.mesh");
	mNode = RenderManager::GetInstance()->getSceneManager()->getRootSceneNode()->createChildSceneNode();
	mNode->attachObject(mEntity);

	scale();
}

void MeshRenderer::scale() {
	transformRf = entity->getComponent<Transform>();
	CustomVector3 scaleT = transformRf->getScale();

	mNode->setScale(Ogre::Vector3(scaleT[0], scaleT[1], scaleT[2]));
}

void MeshRenderer::syncPosition(){
	CustomVector3 pos = transformRf->getPosition();
	mNode->setPosition(Ogre::Vector3(pos.x,pos.y, pos.z));
}
