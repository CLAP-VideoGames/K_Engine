#pragma once
#ifndef UIBUTTON_H
#define UIBUTTON_H

#include <ui_prj/Rectangle.h>
#include <ui_prj/UiElement.h>

namespace K_Engine {
	class InputManager;

	class UIButton : public UIElement
	{
	public:

		UIButton(std::string overlayName, std::string imageName, std::string hoverImageName, std::string pressedImageName);
		virtual ~UIButton();

	private:
		std::string imageName_;

		//Extra images for button
		std::string hoverImageName_;
		std::string pressedImageName_;
	};
}
#endif // UIBUTTON_H