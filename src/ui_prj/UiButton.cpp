#include "UIButton.h"

#include <iostream>

#include <OgreOverlay.h>
#include <OgreOverlayManager.h>
#include <OgreOverlayContainer.h>
#include <OgreTextAreaOverlayElement.h>

#include <input_prj/InputManager.h>

#include <utils_prj/checkML.h>

namespace K_Engine {

	static int numberButtons = 0;

	UIButton::UIButton(std::string overlayName, std::string imageName, std::string hoverImageName, std::string pressedImageName) : UIElement(Ogre::OverlayManager::getSingletonPtr())
	{
		//Initialization of everything that ogre needs to show something
		//Default settings
		std::string numOfElements = std::to_string(numberButtons);

		element_ = static_cast<Ogre::OverlayContainer*>(
			oveMngr_->createOverlayElement("Panel", "Button" + numOfElements));
		element_->setMetricsMode(Ogre::GMM_PIXELS);
		element_->setPosition(defaultX, defaultY);
		element_->setDimensions(defaultWidth, defaultHeight);

		//DefaultMaterial
		element_->setMaterialName(imageName);

		// Create an overlay, and add the panel
		overlay_ = oveMngr_->create(overlayName);
		overlay_->add2D(element_);

		// Show the overlay
		overlay_->show();

		size = std::pair<int, int>(400, 150);

		inputMan = K_Engine::InputManager::GetInstance();

		inputArea.h = element_->getHeight();
		inputArea.w = element_->getWidth();
		inputArea.x = element_->getLeft();
		inputArea.y = element_->getTop();

		numberButtons++;

		imageName_ = imageName;
		hoverImageName_ = hoverImageName;
		pressedImageName_ = pressedImageName;
	}

	UIButton::~UIButton() = default;

	void UIButton::update() {

		inputArea.h = element_->getHeight();
		inputArea.w = element_->getWidth();
		inputArea.x = element_->getLeft();
		inputArea.y = element_->getTop();

		Point pointer;
		auto pointPos = inputMan->getMousePos();
		pointer.x = pointPos.first;
		pointer.y = pointPos.second;

		pressed_ = false;

		if (PointInRect(&pointer, &inputArea)) {
			
			if (inputMan->getLeftMouseButtonPressed()) {
				pressed_ = true;

				setMaterial(pressedImageName_);
			}
			else setMaterial(hoverImageName_);
		}
		else setMaterial(imageName_);
		
	}
}