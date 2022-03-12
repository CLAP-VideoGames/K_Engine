#include "MeshRenderer.h"

#include "Entity.h"
#include "Transform.h"

#include <render_prj/RenderManager.h>

#include <OgreEntity.h>
#include <OgreSceneNode.h>
#include <OgreSceneManager.h>

std::string MeshRenderer::name = "MeshRenderer";

MeshRenderer::MeshRenderer() : Component("MeshRenderer", nullptr)
{
	name = id;
}

MeshRenderer::MeshRenderer(Entity* e) : Component("Transform", e) { }

MeshRenderer::~MeshRenderer() {}

void MeshRenderer::debug()
{
	setSinbad();
	setMaterial("Ogre/Skin");
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

void MeshRenderer::scale()
{
	Transform* trans = entity->getComponent<Transform>();
	float* scaleT = trans->getScale();

	mNode->setScale(Ogre::Vector3(scaleT));
}
