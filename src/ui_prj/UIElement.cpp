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

		isInteractive_ = false;
		isFocusNow_ = false;
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

	void UIElement::setPosition(double x, double y) {
		overlayElement_->setPosition(x, y);
	}

	void UIElement::setSize(double w, double h) {
		overlayElement_->setDimensions(w, h);
	}

	void UIElement::setTop(double topValue) {
		overlayElement_->setTop(topValue);
	}

	void UIElement::setLeft(double leftValue) {
		overlayElement_->setLeft(leftValue);
	}

	void UIElement::setWidth(double widthValue) {
		overlayElement_->setWidth(widthValue);
	}

	void UIElement::setHeight(double heightValue) {
		overlayElement_->setHeight(heightValue);
	}

	void UIElement::setMetrics(Metrics m) {
		if (m == PIXELS) overlayElement_->setMetricsMode(Ogre::GMM_PIXELS);
		else if (m == WINDOW_RELATIVE) overlayElement_->setMetricsMode(Ogre::GMM_RELATIVE);
	}

	void UIElement::setRenderOrder(int z) {
		overlay_->setZOrder(z);
	}

	std::pair<double, double> UIElement::getPosition() {
		return { overlayElement_->getLeft(), overlayElement_->getTop() };
	}

	std::pair<double, double> UIElement::getSize() {
		return { overlayElement_->getWidth(), overlayElement_->getHeight() };
	}

	std::string UIElement::getOverlayName() {
		return overlay_->getName();
	}

	bool UIElement::isVisible() {
		return overlay_->isVisible();
	}

	void UIElement::setInteractive(bool isInteractive) {
		isInteractive_ = isInteractive;
	}

	void UIElement::setFocusNow(bool isFocusNow) {
		isFocusNow_ = isFocusNow;
	}

	bool UIElement::getIsInteractive() {
		return isInteractive_;
	}

	bool UIElement::getIsFocusNow() {
		return isFocusNow_;
	}
}