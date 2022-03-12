#include "MeshRenderer.h"

#include "Entity.h"
#include "Transform.h"

#include <render_prj/RenderManager.h>

#include <OgreEntity.h>
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
}

void MeshRenderer::setVisible(bool value) {
	visible = value;
}

void MeshRenderer::setMaterial(std::string nMaterial) {
	material = nMaterial;
}

void MeshRenderer::setSinbad()
{
	ogreNode = RenderManager::GetInstance()->getSceneManager()->getRootSceneNode()->createChildSceneNode();

	ogreNode->attachObject(RenderManager::GetInstance()->getSceneManager()->createEntity("ogrehead.mesh"));

	scale();
}

void MeshRenderer::scale()
{
	Transform* trans = entity->getComponent<Transform>();
	float* scaleT = trans->getScale();

	ogreNode->setScale(Ogre::Vector3(scaleT));
}
