#include "UISlider.h"

#include <OgreOverlay.h>
#include <OgreOverlayManager.h>
#include <OgreOverlayContainer.h>
#include <OgreTextAreaOverlayElement.h>

#include <utils_prj/Vector3.h>
#include <utils_prj/checkML.h>

namespace K_Engine {

	UISlider::UISlider(std::string overlayName, std::string imageName, int y, int left, int right, int initialPosition) : UIElement()
	{
		//Initialization of everything that ogre needs to show something
		//Default settings
		overlayElement_ = static_cast<Ogre::OverlayContainer*>(overlayMan_->createOverlayElement("Panel", imageName + std::to_string(numOverlayElems)));
		overlayElement_->setMetricsMode(Ogre::GMM_RELATIVE);
		overlayElement_->setPosition(left + (right - left - (right - left) / 10) * initialPosition, y);

		//DefaultMaterial
		overlayElement_->setMaterialName(imageName);

		// Create an overlay, and add the panel
		overlay_ = overlayMan_->create(overlayName + std::to_string(numOverlayElems));
		overlay_->add2D(overlayElement_);

		// Show the overlay
		overlay_->show();

		//Setup the movement limits of the scrollbar
		leftLimit = left;
		rightLimit = right;

		//Setup default size relative to the total distance
		distance = right - left;
		initialDistance = distance;
		if (distance / 10 > 0) 
			overlayElement_->setDimensions(distance / 10, 20);
		else overlayElement_->setDimensions(distance, 20);
	}

	UISlider::~UISlider() = default;

	//Returns the percentage of the scrollbar that is left above the scrollbar itself
	//this means that 100 is when the bar is on top and the closer it gets to 0 the lower it is.
	double UISlider::getRelativePos() {
		return (((double)overlayElement_->getLeft() - (double)leftLimit) / ((double)distance - overlayElement_->getWidth())) * 100;
	}
	void UISlider::setLeftLimit(int newLeftLimit)
	{
		leftLimit = newLeftLimit;
	}
	void UISlider::setRightLimit(int newRightLimit)
	{
		rightLimit = newRightLimit;
	}
}