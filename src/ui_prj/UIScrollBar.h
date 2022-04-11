#pragma once
#ifndef UISCROLLBAR_H
#define UISCROLLBAR_H
#include "UiElement.h"
#include "Rectangle.h"

namespace K_Engine {
	class InputManager;

	class UiScrollBar : public UiElement
	{
	public:

		UiScrollBar(std::string overlayName, std::string imageName, int upper, int lower);
		~UiScrollBar();

		virtual void update();

		double getRelativePos();

	private:

		InputManager* inputMan;

		Rectangle inputArea;

		int upperLimit, lowerLimit;
		int distance;

		bool pressed = false;
	};
}


#endif