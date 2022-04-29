#pragma once
#ifndef UIBUTTON_H
#define UIBUTTON_H

#include <ui_prj/UIElement.h>

namespace K_Engine {
	class UIButton : public UIElement
	{
	public:
		UIButton(std::string overlayName, std::string imageName, std::string hoverImageName, std::string pressedImageName);
		virtual ~UIButton();
	};
}
#endif // UIBUTTON_H