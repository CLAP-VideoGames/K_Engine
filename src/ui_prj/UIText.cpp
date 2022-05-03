#include "UIText.h"

#include <OgreOverlayContainer.h>
#include <OgreOverlayManager.h>
#include <OgreTextAreaOverlayElement.h>
#include <OgreOverlay.h>

#include <utils_prj/checkML.h>

namespace K_Engine {
	UIText::UIText(std::string overlayName, std::string fontName, float x, float y, float width, float height, std::string text, Vector3 textColor) : UIElement()
	{
        textArea_ = static_cast<Ogre::TextAreaOverlayElement*>(
			overlayMan_->createOverlayElement("TextArea", overlayName + std::to_string(numOverlayElems)));

        textArea_->setMetricsMode(Ogre::GMM_RELATIVE);
        textArea_->setPosition(x, y);
        textArea_->setDimensions(width, height);
        textArea_->setCaption(text);
        textArea_->setCharHeight(height);

        //Default font
        textArea_->setFontName(fontName);
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
		textArea_->setCharHeight(h);
	}

	void UIText::setFont(std::string fontName) {
		textArea_->setFontName(fontName);
	}

	void UIText::setText(std::string newText) {
		textArea_->setCaption(newText);
	}

	void UIText::setTextColor(Vector3 newColor) {
		textArea_->setColourBottom(Ogre::ColourValue(newColor.x, newColor.y, newColor.z));
		textArea_->setColourTop(Ogre::ColourValue(newColor.x, newColor.y, newColor.z));
	}

	std::pair<double, double> UIText::getPosition()
	{
		return { textArea_->getLeft(), textArea_->getTop() };
	}

	std::pair<double, double> UIText::getSize() {
		return { textArea_->getWidth(), textArea_->getHeight() };
	}
	void UIText::setPosition(double x, double y)
	{
		textArea_->setPosition(x, y);
	}
	void UIText::setSize(double w, double h)
	{
		textArea_->setDimensions(w, h);
	}
	void UIText::setTop(double topValue)
	{
		textArea_->setTop(topValue);
	}
	void UIText::setLeft(double leftValue)
	{
		textArea_->setLeft(leftValue);
	}
	void UIText::setWidth(double widthValue)
	{
		textArea_->setWidth(widthValue);
	}
	void UIText::setHeight(double heightValue)
	{
		textArea_->setHeight(heightValue);
	}
}