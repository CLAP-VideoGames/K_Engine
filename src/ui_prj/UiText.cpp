#include "UIText.h"

#include <OgreOverlayContainer.h>
#include <OgreOverlayManager.h>
#include <OgreTextAreaOverlayElement.h>
#include <OgreOverlay.h>

#include <utils_prj/checkML.h>

namespace K_Engine {

    //Number of text so ogre can keep track of every UiElement
    static int numberOfText = 0;

    UIText::UIText(std::string overlayName, std::string fontName, std::string text) : UIElement(Ogre::OverlayManager::getSingletonPtr())
    {
        //Our message
        text_ = text;

        std::string elemtnNumber = std::to_string(numberOfText);

        //Initialization of everything that ogre needs to show something
        Ogre::OverlayContainer* panel = static_cast<Ogre::OverlayContainer*>(
            overlayMan_->createOverlayElement("Panel", "PanelText" + elemtnNumber));
        panel->setMetricsMode(Ogre::GMM_PIXELS);
        panel->setPosition(defaultX, defaultY);
        panel->setDimensions(defaultWidth, defaultWidth);

        textArea = static_cast<Ogre::TextAreaOverlayElement*>(
            overlayMan_->createOverlayElement("TextArea", "TextAreaName" + elemtnNumber));

        textArea->setMetricsMode(Ogre::GMM_PIXELS);
        textArea->setPosition(50, 50);
        textArea->setDimensions(20, 20);
        textArea->setCaption(text_);
        textArea->setCharHeight(40);

        //Default font
        textArea->setFontName(fontName);
        textArea->setColourBottom(Ogre::ColourValue(0.00, 0.00, 0.00));
        textArea->setColourTop(Ogre::ColourValue(0.0, 0.0, 0.0));

        // Create an overlay, and add the panel
        overlay_ = overlayMan_->create(overlayName);
        overlay_->add2D(panel);

        // Add the text area to the panel
        panel->addChild(textArea);

        // Show the overlay
        overlay_->show();

        setText(text_);
        numberOfText++;
    }

    UIText::~UIText() = default;

    void UIText::setText(std::string nText)
    {
        textArea->setCaption(nText);
    }

    void UIText::setSize(int w, int h)
    {
        textArea->setDimensions(w, h);

        size.first = w;
        size.second = h;
    }

    void UIText::setPosition(int x, int y)
    {
        textArea->setPosition(x, y);

        position.first = x;
        position.second = y;
    }

    void UIText::setFont(std::string fontName)
    {
        textArea->setFontName(fontName);
    }
}


