#include "UIProgressBar.h"

#include <OgreOverlay.h>
#include <OgreOverlayManager.h>
#include <OgreOverlayContainer.h>

#include <utils_prj/checkML.h>

namespace K_Engine {
    static int numberOfBars = 0;

    UIProgressBar::UIProgressBar(std::string overlayName, std::string imageName,
        int x, int y, int orgWidth, int orgHeight) : UIElement()
    {
        std::string elemtnNumber = std::to_string(numberOfBars);

        //Initialization of everything that ogre needs to show something
        //Default settings
        overlayElement_ = static_cast<Ogre::OverlayContainer*>(
            overlayMan_->createOverlayElement("Panel", "ProgressBar" + elemtnNumber));
        overlayElement_->setMetricsMode(Ogre::GMM_PIXELS);
        overlayElement_->setPosition(x, y);
        overlayElement_->setDimensions(orgWidth, orgHeight);

        //DefaultMaterial
        overlayElement_->setMaterialName(imageName);

        // Create an overlay, and add the panel
        overlay_ = overlayMan_->create(overlayName);
        overlay_->add2D(overlayElement_);

        // Show the overlay
        overlay_->show();

        numberOfBars++;

        originalSize = std::pair<int, int>(orgWidth, orgHeight);
    }

    UIProgressBar::~UIProgressBar() = default;

    void UIProgressBar::setProgress(float prog) {
        if (prog <= maximumProgresion)  progresion = prog;
        else progresion = maximumProgresion;

        setSize(originalSize.first * (prog / maximumProgresion), originalSize.second);
    }

    void UIProgressBar::setMaxProgress(float maximum) {
        maximumProgresion = maximum;
    }

    float UIProgressBar::getProgress() {
        return progresion;
    }
}


