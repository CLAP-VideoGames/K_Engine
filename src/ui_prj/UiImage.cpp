#include "UIImage.h"

#include <OgreOverlayContainer.h>
#include <OgreOverlayManager.h>
#include <OgreOverlay.h>

#include <utils_prj/checkML.h>

namespace K_Engine {
    static int numberOfImages = 0;

    UIImage::UIImage(std::string overlayName, std::string imageName) : UIElement(Ogre::OverlayManager::getSingletonPtr())
    {
        std::string elemtnNumber = std::to_string(numberOfImages);

        //Initialization of everything that ogre needs to show something
        //Default settings
        element_ = static_cast<Ogre::OverlayContainer*>(overlayMan_->createOverlayElement("Panel", "ImageName" + elemtnNumber));
        element_->setMetricsMode(Ogre::GMM_PIXELS);
        element_->setPosition(defaultX, defaultY);
        element_->setDimensions(defaultWidth, defaultHeight);

        //DefaultMaterial
        element_->setMaterialName(imageName);

        // Create an overlay, and add the panel
        overlay_ = overlayMan_->create(overlayName);
        overlay_->add2D(element_);

        // Show the overlay
        overlay_->show();

        numberOfImages++;

        size = std::pair<int, int>(defaultWidth, defaultHeight);
    }

    UIImage::~UIImage() = default;

    // Changes the material of the image, to a new one
    void UIImage::changeMaterial(std::string newImageName)
    {
        element_->setMaterialName(newImageName);
    }
}

