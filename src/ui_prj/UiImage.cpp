#include "UIImage.h"

#include <OgreOverlay.h>
#include <OgreOverlayManager.h>
#include <OgreOverlayContainer.h>

#include <utils_prj/checkML.h>

namespace K_Engine {
    static int numberOfImages = 0;

    UIImage::UIImage(std::string overlayName, std::string imageName) : UIElement()
    {
        std::string elemtnNumber = std::to_string(numberOfImages);

        //Initialization of everything that ogre needs to show something
        //Default settings
        overlayElement_ = static_cast<Ogre::OverlayContainer*>(overlayMan_->createOverlayElement("Panel", "ImageName" + elemtnNumber));
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

        numberOfImages++;
    }

    UIImage::~UIImage() = default;

    // Changes the material of the image, to a new one
    void UIImage::changeMaterial(std::string newImageName) {
        overlayElement_->setMaterialName(newImageName);
    }
}

