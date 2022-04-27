#include "UIButton.h"

#include <iostream>

#include <OgreOverlay.h>
#include <OgreOverlayManager.h>
#include <OgreOverlayContainer.h>

#include <utils_prj/checkML.h>

namespace K_Engine {

	static int numberButtons = 0;

	UIButton::UIButton(std::string overlayName, std::string imageName, std::string hoverImageName,
		std::string pressedImageName) : UIElement()
	{
		//Initialization of everything that ogre needs to show something
		//Default settings
		std::string numOfElements = std::to_string(numberButtons);

		overlayElement_ = static_cast<Ogre::OverlayContainer*>(
			overlayMan_->createOverlayElement("Panel", "Button" + numOfElements));
		overlayElement_->setMetricsMode(Ogre::GMM_PIXELS);
		overlayElement_->setPosition(DEFAULT_LEFT, DEFAULT_TOP);
		overlayElement_->setDimensions(DEFAULT_WIDTH, DEFAULT_HEIGHT);

		//DefaultMaterial
		overlayElement_->setMaterialName(imageName);

		// Create an overlay, and add the panel
		overlay_ = overlayMan_->create(overlayName);
		overlay_->add2D(overlayElement_);

		// Show the overlay
		overlay_->show();

		numberButtons++;

		imageName_ = imageName;
		hoverImageName_ = hoverImageName;
		pressedImageName_ = pressedImageName;
	}

	UIButton::~UIButton() = default;
}