#pragma once
#ifndef UIBUTTON_H
#define UIBUTTON_H
#include "UiElement.h"
#include "Rectangle.h"

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


#endif