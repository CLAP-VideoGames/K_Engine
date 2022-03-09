#include "MeshRenderer.h"
//Required
std::string MeshRenderer::name = "MeshRenderer";

MeshRenderer::MeshRenderer() : Component("MeshRenderer")
{

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