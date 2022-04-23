#include "UISlider.h"

#include <iostream>

#include <OgreOverlay.h>
#include <OgreOverlayManager.h>
#include <OgreOverlayContainer.h>
#include <OgreTextAreaOverlayElement.h>

#include <input_prj/InputManager.h>

#include <utils_prj/Vector3.h>
#include <utils_prj/checkML.h>

#include <ui_prj/UiProgressBar.h>

namespace K_Engine {

	UISlider::UISlider(std::string overlayName, std::string imageName, int y, int left, int right) : UIElement(Ogre::OverlayManager::getSingletonPtr())
	{
		//Initialization of everything that ogre needs to show something
		//Default settings
		element_ = static_cast<Ogre::OverlayContainer*>(
			oveMngr_->createOverlayElement("Panel", "Slider"));
		element_->setMetricsMode(Ogre::GMM_PIXELS);
		element_->setPosition(right, y);

		//DefaultMaterial
		element_->setMaterialName(imageName);

		// Create an overlay, and add the panel
		overlay_ = oveMngr_->create(overlayName);
		overlay_->add2D(element_);

		// Show the overlay
		overlay_->show();

		inputMan = K_Engine::InputManager::GetInstance();

		//Setup the movement limits of the scrollbar
		leftLimit = left;
		rightLimit = right;

		//Setup default size relative to the total distance
		distance = right - left;
		initialDistance = distance;
		if (distance / 10 > 0) {
			element_->setDimensions(distance / 10, 20);
		}
		else  element_->setDimensions(distance, 20);

		//Setup the input area rectangle
		inputArea.h = element_->getHeight();
		inputArea.w = element_->getWidth();
		inputArea.x = element_->getLeft();
		inputArea.y = element_->getTop();

		progressBar_ = new UIProgressBar(overlayName + " progress", "DefaultProgressBar", left, y, distance, 20);
		progressBar_->setMaxProgress(100);
		progressBar_->setProgress(100);
		progressBar_->setRenderOrder(30);
	}

	UISlider::~UISlider()
	{
		delete progressBar_;
		progressBar_ = nullptr;
	}

	//Returns the percentage of the scrollbar that is left above the scrollbar itself
	//this means that 100 is when the bar is on top and the closer it gets to 0 the lower it is.
	double UISlider::getRelativePos() {
		return (((double)element_->getLeft() - (double)leftLimit) / (double)distance) * 100;
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
		previousTopDistance = element_->getTop() - leftLimit;
		leftLimit = newPosition.y;
		element_->setLeft(newPosition.x);
		rightLimit = leftLimit + distance;
		element_->setTop(previousTopDistance + leftLimit);
	}

	void UISlider::updateSize(float scale)
	{
		element_->setTop((element_->getTop() - leftLimit) / (distance / initialDistance) * scale + leftLimit);
		element_->setHeight(initialDistance * scale / 10);
		element_->setWidth(20 * scale);
		distance = initialDistance * scale;
		rightLimit = leftLimit + distance;
	}

	//Sets the position according to mouse input and pos
	void UISlider::update() {
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
			auto x = element_->getLeft();
			if (x >= leftLimit && x <= rightLimit) {
				if (pointer.x >= leftLimit && pointer.x <= rightLimit) {
					element_->setLeft(pointer.x);
					progressBar_->setProgress(getRelativePos());
					positionNeedsSync = true;
				}
			}
		}
		
		progressBar_->update();
	}
}