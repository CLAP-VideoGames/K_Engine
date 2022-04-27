#pragma once
#ifndef UISCROLLBAR_H
#define UISCROLLBAR_H

#include <ui_prj/UiElement.h>

namespace K_Engine {
	class Vector3;

	class UIScrollBar : public UIElement
	{
	public:
		UIScrollBar(std::string overlayName, std::string imageName, int x, int upper, int lower);
		virtual ~UIScrollBar();

		double getRelativePos();
	private:

		int upperLimit, lowerLimit;
		int initialDistance;
		int distance;

		bool pressed = false;
	};
}
#endif // UISCROLLBAR_H