#include "UiImage.h"
#include <OgreOverlayContainer.h>
#include <OgreOverlayManager.h>
#include <OgreOverlay.h>

namespace K_Engine {
    static int numberOfImages = 0;

    UiImage::UiImage(std::string overlayName, std::string imageName) : UiElement(Ogre::OverlayManager::getSingletonPtr())
    {
        std::string elemtnNumber = std::to_string(numberOfImages);

        //Initialization of everything that ogre needs to show something
        //Default settings
        element_ = static_cast<Ogre::OverlayContainer*>(oveMngr_->createOverlayElement("Panel", "ImageName" + elemtnNumber));
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

        numberOfImages++;

        size = std::pair<int, int>(500, 150);
    }

    UiImage::~UiImage()
    {

    }

    // Changes the material of the image, to a new one
    void UiImage::changeMaterial(std::string newImageName)
    {
        element_->setMaterialName(newImageName);
    }
}

