#include <ui_prj/UIScrollBar.h>

#include <iostream>

#include <OgreOverlay.h>
#include <OgreOverlayManager.h>
#include <OgreOverlayContainer.h>
#include <OgreTextAreaOverlayElement.h>

#include <input_prj/InputManager.h>

#include <utils_prj/Vector3.h>
#include <utils_prj/checkML.h>

namespace K_Engine {

	UIScrollBar::UIScrollBar(std::string overlayName, std::string imageName, int x, int upper, int lower) : UIElement()
	{
		//Initialization of everything that ogre needs to show something
		//Default settings
		overlayElement_ = static_cast<Ogre::OverlayContainer*>(
			overlayMan_->createOverlayElement("Panel", "ScrollBar"));
		overlayElement_->setMetricsMode(Ogre::GMM_PIXELS);
		overlayElement_->setTop(upper);
		overlayElement_->setLeft(x);

		//DefaultMaterial
		overlayElement_->setMaterialName(imageName);

		// Create an overlay, and add the panel
		overlay_ = overlayMan_->create(overlayName);
		overlay_->add2D(overlayElement_);

		// Show the overlay
		overlay_->show();

		inputMan = K_Engine::InputManager::GetInstance();

		//Setup the movement limits of the scrollbar
		upperLimit = upper;
		lowerLimit = lower;

		//Setup default size relative to the total distance
		distance = lower - upper;
		initialDistance = distance;
		if (distance / 10 > 0) 
			overlayElement_->setDimensions(20, distance / 10);
		else overlayElement_->setDimensions(20, distance);

		//Setup the input area rectangle
		inputArea.h = overlayElement_->getHeight();
		inputArea.w = overlayElement_->getWidth();
		inputArea.x = overlayElement_->getLeft();
		inputArea.y = overlayElement_->getTop();

	}

	UIScrollBar::~UIScrollBar() = default;

	//Returns the percentage of the scrollbar that is left above the scrollbar itself
	//this means that 100 is when the bar is on top and the closer it gets to 0 the lower it is.
	double UIScrollBar::getRelativePos() {
		return (((double)overlayElement_->getTop() - (double)upperLimit) / (double)distance) * 100;
	}

	bool UIScrollBar::getNeedsSync() {
		return positionNeedsSync;
	}

	void UIScrollBar::setNeedsSync(bool newState) {
		positionNeedsSync = newState;
	}

	void UIScrollBar::updatePosition(Vector3 newPosition) {
		float previousTopDistance;
		previousTopDistance = overlayElement_->getTop() - upperLimit;
		upperLimit = newPosition.y;
		overlayElement_->setLeft(newPosition.x);
		lowerLimit = upperLimit + distance;
		overlayElement_->setTop(previousTopDistance + upperLimit);
	}

	void UIScrollBar::updateSize(float scale) {
		overlayElement_->setTop((overlayElement_->getTop() - upperLimit) / (distance / initialDistance) * scale + upperLimit);
		overlayElement_->setHeight(initialDistance * scale / 10);
		overlayElement_->setWidth(20 * scale);
		distance = initialDistance * scale;
		lowerLimit = upperLimit + distance;
	}
}