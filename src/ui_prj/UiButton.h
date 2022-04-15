#pragma once
#ifndef UIBUTTON_H
#define UIBUTTON_H

#include <ui_prj/Rectangle.h>
#include <ui_prj/UiElement.h>

namespace K_Engine {
	class InputManager;

	class UiButton : public UiElement
	{
	public:

		UiButton(std::string overlayName, std::string imageName, std::string hoverImageName, std::string pressedImageName);
		~UiButton();

		virtual void update();

		bool getPressed() { return pressed_; };

	private:
		bool pressed_;

		InputManager* inputMan;

		Rectangle inputArea;

		std::string imageName_;

		//Extra images for button
		std::string hoverImageName_;
		std::string pressedImageName_;
	};
}
#endif // UIBUTTON_H