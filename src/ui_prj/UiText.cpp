#include "UiText.h"
#include <OgreOverlayContainer.h>
#include <OgreOverlayManager.h>
#include <OgreTextAreaOverlayElement.h>
#include <OgreOverlay.h>

namespace K_Engine {

    //Number of text so ogre can keep track of every UiElement
    static int numberOfText = 0;

    UiText::UiText(std::string overlayName, std::string text_) : UiElement(Ogre::OverlayManager::getSingletonPtr())
    {
        //Our message
        text = text_;

        std::string elemtnNumber = std::to_string(numberOfText);

        //Initialization of everything that ogre needs to show something
        Ogre::OverlayContainer* panel = static_cast<Ogre::OverlayContainer*>(
            oveMngr_->createOverlayElement("Panel", "PanelText" + elemtnNumber));
        panel->setMetricsMode(Ogre::GMM_PIXELS);
        panel->setPosition(defaultX, defaultY);
        panel->setDimensions(defaultWidth, defaultWidth);

        textArea = static_cast<Ogre::TextAreaOverlayElement*>(
            oveMngr_->createOverlayElement("TextArea", "TextAreaName" + elemtnNumber));

        textArea->setMetricsMode(Ogre::GMM_PIXELS);
        textArea->setPosition(50, 50);
        textArea->setDimensions(20, 20);
        textArea->setCaption(text);
        textArea->setCharHeight(40);
        //Default font
        textArea->setFontName("MyFont");
        textArea->setColourBottom(Ogre::ColourValue(0.03, 0.05, 0.03));
        textArea->setColourTop(Ogre::ColourValue(0.9, 0.95, 0.95));

        // Create an overlay, and add the panel
        overlay_ = oveMngr_->create(overlayName);
        overlay_->add2D(panel);

        // Add the text area to the panel
        panel->addChild(textArea);

        // Show the overlay
        overlay_->show();

        setText(text);
        numberOfText++;
    }

    UiText::~UiText()
    {

    }

    void UiText::setText(std::string nText)
    {
        textArea->setCaption(nText);
    }

    void UiText::setSize(int w, int h)
    {
        textArea->setDimensions(w, h);

        size.first = w;
        size.second = h;
    }

    void UiText::setPosition(int x, int y)
    {
        textArea->setPosition(x, y);

        position.first = x;
        position.second = y;
    }

    void UiText::setFont(std::string fontName)
    {
        textArea->setFontName(fontName);
    }
}


