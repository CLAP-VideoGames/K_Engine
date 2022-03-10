#include "MeshRenderer.h"

#include "Entity.h"
#include "Transform.h"

#include <OgreEntity.h>
#include <OgreSceneManager.h>
#include <render_prj/RenderManager.h>

std::string MeshRenderer::name = "MeshRenderer";

MeshRenderer::MeshRenderer() : Component("MeshRenderer", nullptr)
{
	name = id;

	entity->getComponent<Transform>()->getNode()->createChildSceneNode()->
		attachObject(RenderManager::GetInstance()->getSceneManager()->createEntity("ogrehead.mesh"));
}

MeshRenderer::~MeshRenderer()
{

}

void MeshRenderer::setVisible(bool value) {
	visible = value;
}

void MeshRenderer::setMaterial(std::string nMaterial) {
	material = nMaterial;
}