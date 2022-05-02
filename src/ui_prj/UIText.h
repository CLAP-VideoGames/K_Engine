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
		UIText(std::string overlayName, std::string fontName, float x, float y, float width, float height, std::string text, Vector3 textColor);
		virtual ~UIText();

		//Im pretty sure size is based on font for text
		virtual void setPosition(int x, int y);
		virtual void setSize(int w, int h);

		void setFont(std::string fontName);
		void setText(std::string newText);
		void setTextColor(Vector3 newColor);

		virtual std::pair<double, double> getPosition();
		virtual std::pair<double, double> getSize();

		virtual void setPosition(double x, double y);
		virtual void setSize(double w, double h);

		virtual void setTop(double topValue);
		virtual void setLeft(double leftValue);

		virtual void setWidth(double widthValue);
		virtual void setHeight(double heightValue);

	private:
		Ogre::TextAreaOverlayElement* textArea_;
	};
}
#endif // UITEXT_H