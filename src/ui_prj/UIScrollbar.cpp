#include <ui_prj/UIScrollBar.h>

#include <OgreOverlay.h>
#include <OgreOverlayManager.h>
#include <OgreOverlayContainer.h>
#include <OgreTextAreaOverlayElement.h>

#include <utils_prj/Vector3.h>
#include <utils_prj/checkML.h>

namespace K_Engine {

	UIScrollBar::UIScrollBar(std::string overlayName, std::string imageName, int x, int upper, int lower) : UIElement(Ogre::OverlayManager::getSingletonPtr())
	{
		//Initialization of everything that ogre needs to show something
		//Default settings
		element_ = static_cast<Ogre::OverlayContainer*>(
			overlayMan_->createOverlayElement("Panel", "ScrollBar"));
		element_->setMetricsMode(Ogre::GMM_PIXELS);
		element_->setTop(upper);
		element_->setLeft(x);

		//DefaultMaterial
		element_->setMaterialName(imageName);

		// Create an overlay, and add the panel
		overlay_ = overlayMan_->create(overlayName);
		overlay_->add2D(element_);

		// Show the overlay
		overlay_->show();

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

	}

	UIScrollBar::~UIScrollBar()
	{

	}

	//Returns the percentage of the scrollbar that is left above the scrollbar itself
	//this means that 100 is when the bar is on top and the closer it gets to 0 the lower it is.
	double UIScrollBar::getRelativePos() {
		return (((double)element_->getTop() - (double)upperLimit) / (double)distance) * 100;
	}
}