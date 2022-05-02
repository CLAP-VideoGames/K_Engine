#include "UIButton.h"

#include <iostream>

#include <OgreOverlay.h>
#include <OgreOverlayManager.h>
#include <OgreOverlayContainer.h>

#include <utils_prj/checkML.h>

namespace K_Engine {
	UIButton::UIButton(std::string overlayName, std::string imageName, std::string hoverImageName,
		std::string pressedImageName) : UIElement()
	{
		//Default settings
		overlayElement_ = static_cast<Ogre::OverlayContainer*>(
			overlayMan_->createOverlayElement("Panel", imageName + std::to_string(numOverlayElems)));
		overlayElement_->setMetricsMode(Ogre::GMM_RELATIVE);
		overlayElement_->setPosition(DEFAULT_LEFT, DEFAULT_TOP);
		overlayElement_->setDimensions(DEFAULT_WIDTH, DEFAULT_HEIGHT);

		//DefaultMaterial
		overlayElement_->setMaterialName(imageName);

		// Create an overlay, and add the panel
		overlay_ = overlayMan_->create(overlayName + std::to_string(numOverlayElems));
		overlay_->add2D(overlayElement_);

		// Show the overlay
		overlay_->show();
	}

	UIButton::~UIButton() = default;
}