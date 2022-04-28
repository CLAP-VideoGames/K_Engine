#include "UIElement.h"

#include <OgreOverlay.h>
#include <OgreOverlayContainer.h>
#include <OgreRenderTarget.h>
#include <OgreOverlayManager.h>
#include <OgreTextAreaOverlayElement.h>

#include <render_prj/RenderManager.h>

#include <utils_prj/checkML.h>

namespace K_Engine {
	int UIElement::numOverlayElems = 0;

	UIElement::UIElement() {
		overlayMan_ = Ogre::OverlayManager::getSingletonPtr();

		numOverlayElems++;
	}

	UIElement::~UIElement() {
		overlayMan_->destroy(overlay_);
	}

	void UIElement::show() {
		overlay_->show();
	}

	void UIElement::hide() {
		overlay_->hide();
	}

	void UIElement::setMaterial(std::string const& materialName) {
		overlayElement_->setMaterialName(materialName);
	}

	void UIElement::setPosition(int x, int y) {
		overlayElement_->setPosition(x, y);
	}

	void UIElement::setSize(int w, int h) {
		overlayElement_->setDimensions(w, h);
	}

	void UIElement::setTop(int topValue) {
		overlayElement_->setTop(topValue);
	}

	void UIElement::setLeft(int leftValue) {
		overlayElement_->setLeft(leftValue);
	}

	void UIElement::setWidth(int widthValue)
	{
		overlayElement_->setWidth(widthValue);
	}

	void UIElement::setHeight(int heightValue)
	{
		overlayElement_->setHeight(heightValue);
	}

	void UIElement::setMetrics(Metrics m) {
		if (m == PIXELS) overlayElement_->setMetricsMode(Ogre::GMM_PIXELS);
		else if (m == WINDOW_RELATIVE) overlayElement_->setMetricsMode(Ogre::GMM_RELATIVE);
	}

	void UIElement::setRenderOrder(int z) {
		overlay_->setZOrder(z);
	}

	std::pair<int, int> UIElement::getPosition() {
		return { overlayElement_->getLeft(), overlayElement_->getTop() };
	}

	std::pair<int, int> UIElement::getSize() {
		return { overlayElement_->getWidth(), overlayElement_->getHeight() };
	}
}