#pragma once
#ifndef UITEXT_H
#define UITEXT_H

#include <string>

#include <ui_prj/UiElement.h>

namespace Ogre {
	class TextAreaOverlayElement;
}

namespace K_Engine {
	/// <summary>
	/// Our text class, overlayName is the interName ogre will record your overlay
	/// text_ is the message our text will show
	/// </summary>
	class UIText : public UIElement
	{
	public:
		UIText(std::string overlayName, std::string fontName, std::string text);

		virtual ~UIText();

		//Im pretty sure size is based on font for text
		virtual void setPosition(int x, int y);
		virtual void setSize(int w, int h);

		void setFont(std::string fontName);
		void setText(std::string newText);

		std::string getText();

	private:
		Ogre::TextAreaOverlayElement* textArea_;

		std::string text_;
	};
}
#endif // UITEXT_H