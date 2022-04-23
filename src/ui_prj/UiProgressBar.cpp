#include "UIProgressBar.h"

#include <OgreOverlayContainer.h>
#include <OgreOverlayManager.h>
#include <OgreTextAreaOverlayElement.h>
#include <OgreOverlay.h>

#include <utils_prj/checkML.h>

namespace K_Engine {
    static int numberOfBars = 0;

    UIProgressBar::UIProgressBar(std::string overlayName, std::string imageName, int x, int y, int orgWidth, int orgHeight) : UIElement(Ogre::OverlayManager::getSingletonPtr())
    {
        std::string elemtnNumber = std::to_string(numberOfBars);

        //Initialization of everything that ogre needs to show something
        //Default settings
        element_ = static_cast<Ogre::OverlayContainer*>(
            oveMngr_->createOverlayElement("Panel", "ProgressBar" + elemtnNumber));
        element_->setMetricsMode(Ogre::GMM_PIXELS);
        element_->setPosition(x, y);
        element_->setDimensions(orgWidth, orgHeight);

        //DefaultMaterial
        element_->setMaterialName(imageName);

        // Create an overlay, and add the panel
        overlay_ = oveMngr_->create(overlayName);
        overlay_->add2D(element_);

        // Show the overlay
        overlay_->show();

        numberOfBars++;

        originalSize = std::pair<int, int>(orgWidth, orgHeight);
    }

    UIProgressBar::~UIProgressBar() = default;

    void UIProgressBar::setProgress(float prog)
    {
        if (prog <= maximumProgresion)  progresion = prog;
        else progresion = maximumProgresion;

        setSize(originalSize.first * (prog / maximumProgresion), originalSize.second);
    }

    void UIProgressBar::setMaxProgress(float maximum)
    {
        maximumProgresion = maximum;
    }

    float UIProgressBar::getProgress()
    {
        return progresion;
    }
}


