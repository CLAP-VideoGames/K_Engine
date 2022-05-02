#pragma once
#ifndef UISLIDER_H
#define UISLIDER_H

#include <ui_prj/UiElement.h>

namespace K_Engine {
	class Vector3;

	class UISlider : public UIElement
	{
	public:
		UISlider(std::string overlayName, std::string imageName, float x, float y, float width, float height, float initialPosition);
		virtual ~UISlider();

		double getRelativePos();

		void setLeftLimit(int newLeftLimit);
		void setRightLimit(int newRightLimit);

		virtual void setSize(double width, double height);

	private:
		float leftLimit, rightLimit;
		float width_, height_;
		float initialDistance;

		bool pressed = false;
	};
}
#endif // UISLIDER_H