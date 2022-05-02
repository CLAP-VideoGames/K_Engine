#pragma once
#ifndef UITEXT_H
#define UITEXT_H

#include <string>

#include <utils_prj/Vector3.h>

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
		UIText(std::string overlayName, std::string fontName, int fontSize, std::string text, Vector3 textColor);
		virtual ~UIText();

		//Im pretty sure size is based on font for text
		virtual void setPosition(int x, int y);
		virtual void setSize(int w, int h);

		void setFont(std::string fontName);
		void setFontSize(int newSize);
		void setText(std::string newText);
		void setTextColor(Vector3 newColor);

		virtual std::pair<double, double> getSize();

	private:
		Ogre::TextAreaOverlayElement* textArea_;
	};
}
#endif // UITEXT_H