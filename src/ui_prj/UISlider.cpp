#include "UISlider.h"

#include <iostream>

#include <OgreOverlay.h>
#include <OgreOverlayManager.h>
#include <OgreOverlayContainer.h>
#include <OgreTextAreaOverlayElement.h>

#include <input_prj/InputManager.h>

#include <utils_prj/Vector3.h>
#include <utils_prj/checkML.h>

namespace K_Engine {

	UISlider::UISlider(std::string overlayName, std::string imageName, int y, int left, int right) : UIElement()
	{
		//Initialization of everything that ogre needs to show something
		//Default settings
		overlayElement_ = static_cast<Ogre::OverlayContainer*>(overlayMan_->createOverlayElement("Panel", "Slider"));
		overlayElement_->setMetricsMode(Ogre::GMM_PIXELS);
		overlayElement_->setPosition(right, y);

		//DefaultMaterial
		overlayElement_->setMaterialName(imageName);

		// Create an overlay, and add the panel
		overlay_ = overlayMan_->create(overlayName);
		overlay_->add2D(overlayElement_);

		// Show the overlay
		overlay_->show();

		inputMan = K_Engine::InputManager::GetInstance();

		//Setup the movement limits of the scrollbar
		leftLimit = left;
		rightLimit = right;

		//Setup default size relative to the total distance
		distance = right - left;
		initialDistance = distance;
		if (distance / 10 > 0) 
			overlayElement_->setDimensions(distance / 10, 20);
		else  overlayElement_->setDimensions(distance, 20);

		//Setup the input area rectangle
		inputArea.h = overlayElement_->getHeight();
		inputArea.w = overlayElement_->getWidth();
		inputArea.x = overlayElement_->getLeft();
		inputArea.y = overlayElement_->getTop();
	}

	UISlider::~UISlider()
	{
	}

	//Returns the percentage of the scrollbar that is left above the scrollbar itself
	//this means that 100 is when the bar is on top and the closer it gets to 0 the lower it is.
	double UISlider::getRelativePos() {
		return (((double)overlayElement_->getLeft() - (double)leftLimit) / (double)distance) * 100;
	}

	bool UISlider::getNeedsSync()
	{
		return positionNeedsSync;
	}

	void UISlider::setNeedsSync(bool newState)
	{
		positionNeedsSync = newState;
	}

	void UISlider::updatePosition(Vector3 newPosition)
	{
		float previousTopDistance;
		previousTopDistance = overlayElement_->getTop() - leftLimit;
		leftLimit = newPosition.y;
		overlayElement_->setLeft(newPosition.x);
		rightLimit = leftLimit + distance;
		overlayElement_->setTop(previousTopDistance + leftLimit);
	}

	void UISlider::updateSize(float scale)
	{
		overlayElement_->setTop((overlayElement_->getTop() - leftLimit) / (distance / initialDistance) * scale + leftLimit);
		overlayElement_->setHeight(initialDistance * scale / 10);
		overlayElement_->setWidth(20 * scale);
		distance = initialDistance * scale;
		rightLimit = leftLimit + distance;
	}
}