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

	UIScrollBar::UIScrollBar(std::string overlayName, std::string imageName, int x, int upper, int lower) : UIElement(Ogre::OverlayManager::getSingletonPtr())
	{
		//Initialization of everything that ogre needs to show something
		//Default settings
		element_ = static_cast<Ogre::OverlayContainer*>(
			oveMngr_->createOverlayElement("Panel", "ScrollBar"));
		element_->setMetricsMode(Ogre::GMM_PIXELS);
		element_->setTop(upper);
		element_->setLeft(x);

		//DefaultMaterial
		element_->setMaterialName(imageName);

		// Create an overlay, and add the panel
		overlay_ = oveMngr_->create(overlayName);
		overlay_->add2D(element_);

		// Show the overlay
		overlay_->show();

		inputMan = K_Engine::InputManager::GetInstance();

		//Setup the movement limits of the scrollbar
		upperLimit = upper;
		lowerLimit = lower;

		//Setup default size relative to the total distance
		distance = lower - upper;
		initialDistance = distance;
		if (distance / 10 > 0) {
			element_->setDimensions(20, distance / 10);
		}
		else  element_->setDimensions(20, distance);

		//Setup the input area rectangle
		inputArea.h = element_->getHeight();
		inputArea.w = element_->getWidth();
		inputArea.x = element_->getLeft();
		inputArea.y = element_->getTop();

	}

	UIScrollBar::~UIScrollBar()
	{

	}

	//Returns the percentage of the scrollbar that is left above the scrollbar itself
	//this means that 100 is when the bar is on top and the closer it gets to 0 the lower it is.
	double UIScrollBar::getRelativePos() {
		return (((double)distance - (double)position.second - (double)upperLimit) / (double)distance) * 100;
	}

	bool UIScrollBar::getNeedsSync()
	{
		return positionNeedsSync;
	}

	void UIScrollBar::setNeedsSync(bool newState)
	{
		positionNeedsSync = newState;
	}

	void UIScrollBar::updatePosition(Vector3 newPosition)
	{
		float previousTopDistance;
		previousTopDistance = element_->getTop() - upperLimit;
		upperLimit = newPosition.y;
		element_->setLeft(newPosition.x);
		lowerLimit = upperLimit + distance;
		element_->setTop(previousTopDistance + upperLimit);
	}

	void UIScrollBar::updateSize(float scale)
	{
		element_->setTop((element_->getTop() - upperLimit) / (distance / initialDistance) * scale + upperLimit);
		element_->setHeight(initialDistance * scale / 10);
		element_->setWidth(20 * scale);
		distance = initialDistance * scale;
		lowerLimit = upperLimit + distance;
	}

	//Sets the position according to mouse input and pos
	void UIScrollBar::update() {
		//Setup the input area rectangle
		inputArea.h = element_->getHeight();
		inputArea.w = element_->getWidth();
		inputArea.x = element_->getLeft();
		inputArea.y = element_->getTop();

		Point pointer;
		auto pointPos = inputMan->getMousePos();
		pointer.x = pointPos.first;
		pointer.y = pointPos.second;

		if (inputMan->getLeftMouseButtonPressed())
		{
			if (PointInRect(&pointer, &inputArea)) {
				pressed = true;
			}
		}
		else
			pressed = false;

		if (pressed) {
			auto y = element_->getTop();
			if (y >= upperLimit && y <= lowerLimit) {
				if (pointer.y >= upperLimit && pointer.y <= lowerLimit) {
					element_->setTop(pointer.y);
					positionNeedsSync = true;
				}
			}
		}
	}
}