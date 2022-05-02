#include "UIImage.h"

#include <OgreOverlay.h>
#include <OgreOverlayManager.h>
#include <OgreOverlayContainer.h>

#include <utils_prj/checkML.h>

namespace K_Engine {
    UIImage::UIImage(std::string overlayName, std::string imageName) : UIElement()
    {
        //Initialization of everything that ogre needs to show something
        //Default settings
        overlayElement_ = static_cast<Ogre::OverlayContainer*>(overlayMan_->createOverlayElement("Panel", imageName + std::to_string(numOverlayElems)));
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

    UIImage::~UIImage() = default;

    void UIImage::setDimensions(int width, int height)
    {
        overlayElement_->setDimensions(width, height);
    }
}

