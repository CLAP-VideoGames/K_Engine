#include "UIText.h"

#include <OgreOverlayContainer.h>
#include <OgreOverlayManager.h>
#include <OgreTextAreaOverlayElement.h>
#include <OgreOverlay.h>

#include <utils_prj/checkML.h>

namespace K_Engine {

    //Number of text so ogre can keep track of every UiElement
    static int numberOfText = 0;

    UIText::UIText(std::string overlayName, std::string fontName, std::string text) : UIElement()
    {
        //Our message
        text_ = text;

        std::string elemtnNumber = std::to_string(numberOfText);

        //Initialization of everything that ogre needs to show something
        overlayElement_ = static_cast<Ogre::OverlayContainer*>(
            overlayMan_->createOverlayElement("Panel", "PanelText" + elemtnNumber));
        overlayElement_->setMetricsMode(Ogre::GMM_PIXELS);
        overlayElement_->setPosition(DEFAULT_LEFT, DEFAULT_TOP);
        overlayElement_->setDimensions(DEFAULT_WIDTH, DEFAULT_HEIGHT);

        textArea_ = static_cast<Ogre::TextAreaOverlayElement*>(
            overlayMan_->createOverlayElement("TextArea", "TextAreaName" + elemtnNumber));

        textArea_->setMetricsMode(Ogre::GMM_PIXELS);
        textArea_->setPosition(50, 50);
        textArea_->setDimensions(20, 20);
        textArea_->setCaption(text_);
        textArea_->setCharHeight(40);

        //Default font
        textArea_->setFontName(fontName);
        textArea_->setColourBottom(Ogre::ColourValue(0.00, 0.00, 0.00));
        textArea_->setColourTop(Ogre::ColourValue(0.0, 0.0, 0.0));

        // Create an overlay, and add the panel
        overlay_ = overlayMan_->create(overlayName);
        overlay_->add2D(overlayElement_);

        // Add the text area to the panel
        overlayElement_->addChild(textArea_);

        // Show the overlay
        overlay_->show();

        setText(text_);
        numberOfText++;
    }

    UIText::~UIText() = default;

    void UIText::setPosition(int x, int y) {
        textArea_->setPosition(x, y);
    }

    void UIText::setSize(int w, int h) {
        textArea_->setDimensions(w, h);
    }

    void UIText::setFont(std::string fontName) {
        textArea_->setFontName(fontName);
    }

    void UIText::setText(std::string newText) {
        textArea_->setCaption(newText);
    }

    std::string UIText::getText() { return text_; }
}


