#include "UiElement.h"
#include <OgreOverlay.h>
#include <OgreOverlayContainer.h>
#include <render_prj/RenderManager.h>
#include <OgreRenderTarget.h>
#include <OgreOverlayManager.h>
#include <OgreTextAreaOverlayElement.h>

UiElement::UiElement(Ogre::OverlayManager* man)
{
	oveMngr_ = man;

	size = std::pair<int, int>(defaultWidth, defaultHeight);

	position = std::pair<int, int>(defaultX, defaultY);
}

UiElement::~UiElement()
{

}

void UiElement::show()
{
	overlay_->show();
}

void UiElement::hide()
{
	overlay_->hide();
}

void UiElement::setMaterial(std::string const& materialName)
{
	element_->setMaterialName(materialName);
}

std::pair<int, int> UiElement::getPosition()
{

	return position;
}

std::pair<int, int> UiElement::getSize()
{
	return size;
}

void UiElement::setPosition(int x, int y)
{
	element_->setPosition(x, y);

	position.first = x;
	position.second = y;
}

void UiElement::setSize(int w, int h)
{
	element_->setDimensions(w, h);

	size.first = w;
	size.second = h;
}

void UiElement::setMetrics(Metrics m)
{
	if (m == Pixels) element_->setMetricsMode(Ogre::GMM_PIXELS);
	else if(m == WindowRelative) element_->setMetricsMode(Ogre::GMM_RELATIVE);
}
