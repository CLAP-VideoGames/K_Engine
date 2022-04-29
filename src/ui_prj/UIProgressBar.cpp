#include "UIProgressBar.h"

#include <OgreOverlay.h>
#include <OgreOverlayManager.h>
#include <OgreOverlayContainer.h>

#include <utils_prj/checkML.h>

namespace K_Engine {
    UIProgressBar::UIProgressBar(std::string overlayName, std::string imageName,
        int orgWidth, int orgHeight) : UIElement()
    {
        //Initialization of everything that ogre needs to show something
        //Default settings
        overlayElement_ = static_cast<Ogre::OverlayContainer*>(overlayMan_->createOverlayElement("Panel", imageName + std::to_string(numOverlayElems)));
        overlayElement_->setMetricsMode(Ogre::GMM_PIXELS);
        overlayElement_->setDimensions(orgWidth, orgHeight);

        //DefaultMaterial
        overlayElement_->setMaterialName(imageName);

        // Create an overlay, and add the panel
        overlay_ = overlayMan_->create(overlayName + std::to_string(numOverlayElems));
        overlay_->add2D(overlayElement_);

        // Show the overlay
        overlay_->show();
    }

    UIProgressBar::~UIProgressBar() = default;
}