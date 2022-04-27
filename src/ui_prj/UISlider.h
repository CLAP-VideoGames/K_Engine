#pragma once
#ifndef UISLIDER_H
#define UISLIDER_H

#include <ui_prj/UiElement.h>

namespace K_Engine {
	class Vector3;

	class UISlider : public UIElement
	{
	public:
		UISlider(std::string overlayName, std::string imageName, int y, int left, int right);
		virtual ~UISlider();

		double getRelativePos();

	private:
		int leftLimit, rightLimit;
		int initialDistance;
		int distance;

		bool pressed = false;
	};
}
#endif // UISLIDER_H