#include "UIText.h"

#include <OgreOverlayContainer.h>
#include <OgreOverlayManager.h>
#include <OgreTextAreaOverlayElement.h>
#include <OgreOverlay.h>

#include <utils_prj/checkML.h>

namespace K_Engine {
	UIText::UIText(std::string overlayName, std::string fontName, int fontSize, std::string text, Vector3 textColor) : UIElement()
	{
		//Initialization of everything that ogre needs to show something
		textArea_ = static_cast<Ogre::TextAreaOverlayElement*>(overlayMan_->createOverlayElement("Panel", fontName + std::to_string(numOverlayElems)));
		textArea_->setMetricsMode(Ogre::GMM_PIXELS);
		textArea_->setPosition(DEFAULT_LEFT, DEFAULT_TOP);
		textArea_->setDimensions(DEFAULT_WIDTH, DEFAULT_HEIGHT);

		textArea_->setMetricsMode(Ogre::GMM_PIXELS);
		textArea_->setCaption(text);
		textArea_->setCharHeight(fontSize);

		//Default font
		//textArea_->setFontName(fontName);
		textArea_->setColourBottom(Ogre::ColourValue(textColor.x, textColor.y, textColor.z));
		textArea_->setColourTop(Ogre::ColourValue(textColor.x, textColor.y, textColor.z));

		// Create an overlay, and add the panel
		overlay_ = overlayMan_->create(overlayName + std::to_string(numOverlayElems));
		overlay_->add2D((Ogre::OverlayContainer*)textArea_);

		// Show the overlay
		overlay_->show();
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

	void UIText::setFontSize(int newSize) {
		textArea_->setCharHeight(newSize);
	}

	void UIText::setText(std::string newText) {
		textArea_->setCaption(newText);
	}

	void UIText::setTextColor(Vector3 newColor) {
		textArea_->setColourBottom(Ogre::ColourValue(newColor.x, newColor.y, newColor.z));
		textArea_->setColourTop(Ogre::ColourValue(newColor.x, newColor.y, newColor.z));
	}
	std::pair<int, int> UIText::getSize()
	{
		return { textArea_->getWidth(), textArea_->getHeight() };
	}
}