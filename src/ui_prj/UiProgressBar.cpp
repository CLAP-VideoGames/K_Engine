#include "UiProgressBar.h"

#include <OgreOverlayContainer.h>
#include <OgreOverlayManager.h>
#include <OgreTextAreaOverlayElement.h>
#include <OgreOverlay.h>

#include <utils_prj/checkML.h>

namespace K_Engine {
    static int numberOfBars = 0;

    UiProgressBar::UiProgressBar(std::string overlayName, std::string imageName) : UiElement(Ogre::OverlayManager::getSingletonPtr())
    {
        std::string elemtnNumber = std::to_string(numberOfBars);

        //Initialization of everything that ogre needs to show something
        //Default settings
        element_ = static_cast<Ogre::OverlayContainer*>(
            oveMngr_->createOverlayElement("Panel", "ProgressBar" + elemtnNumber));
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

        numberOfBars++;

        size = std::pair<int, int>(500, 150);
    }

    UiProgressBar::~UiProgressBar() = default;

    void UiProgressBar::setProgress(float prog)
    {
        if (prog <= maximumProgresion)  progresion = prog;
        else progresion = maximumProgresion;


        std::pair<int, int> oldSize = getSize();

        setSize(oldSize.first * (prog / maximumProgresion), oldSize.second);
    }

    void UiProgressBar::setMaxProgress(float maximum)
    {
        maximumProgresion = maximum;
    }

    float UiProgressBar::getProgress()
    {
        return progresion;
    }
}


