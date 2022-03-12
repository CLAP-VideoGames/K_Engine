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

MeshRenderer::~MeshRenderer()
{

}

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

	ogreEntity = RenderManager::GetInstance()->getSceneManager()->createEntity("ogrehead.mesh");

	ogreNode->attachObject(ogreEntity);
}

void MeshRenderer::scale()
{
	//Transform* t = entity->getComponent<Transform>();
}
