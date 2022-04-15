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
	class UiText : public UiElement
	{
	public:
		UiText(std::string overlayName, std::string text_);
		~UiText();

		void setText(std::string nText);

		//Im pretty sure size is based on font for text
		virtual void setSize(int w, int h);

		virtual void setPosition(int x, int y);

		void setFont(std::string fontName);

		std::string getText() { return text; }

	private:
		std::string text;
		Ogre::TextAreaOverlayElement* textArea;
	};
}
#endif // UITEXT_H