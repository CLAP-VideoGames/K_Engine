#include <ui_prj/UIScrollBar.h>

#include <OgreOverlay.h>
#include <OgreOverlayManager.h>
#include <OgreOverlayContainer.h>
#include <OgreTextAreaOverlayElement.h>

#include <utils_prj/Vector3.h>
#include <utils_prj/checkML.h>

namespace K_Engine {

	UIScrollBar::UIScrollBar(std::string overlayName, std::string imageName, int x, int upper, int lower) : UIElement()
	{
		//Initialization of everything that ogre needs to show something
		//Default settings
		overlayElement_ = static_cast<Ogre::OverlayContainer*>(
			overlayMan_->createOverlayElement("Panel", imageName + std::to_string(numOverlayElems)));
		overlayElement_->setMetricsMode(Ogre::GMM_RELATIVE);
		overlayElement_->setTop(upper);
		overlayElement_->setLeft(x);

		//DefaultMaterial
		overlayElement_->setMaterialName(imageName);

		// Create an overlay, and add the panel
		overlay_ = overlayMan_->create(overlayName + std::to_string(numOverlayElems));
		overlay_->add2D(overlayElement_);

		// Show the overlay
		overlay_->show();

		//Setup the movement limits of the scrollbar
		upperLimit = upper;
		lowerLimit = lower;

		//Setup default size relative to the total distance
		distance = lower - upper;
		initialDistance = distance;
		if (distance / 10 > 0) 
			overlayElement_->setDimensions(20, distance / 10);
		else overlayElement_->setDimensions(20, distance);

	}

	UIScrollBar::~UIScrollBar() = default;

	//Returns the percentage of the scrollbar that is left above the scrollbar itself
	//this means that 100 is when the bar is on top and the closer it gets to 0 the lower it is.
	double UIScrollBar::getRelativePos() {
		return (((double)overlayElement_->getTop() - (double)upperLimit) / (double)distance) * 100;
	}
}