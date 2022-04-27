#pragma once
#ifndef UISLIDER_H
#define UISLIDER_H

#include <ui_prj/Rectangle.h>
#include <ui_prj/UiElement.h>

namespace K_Engine {
	class InputManager;
	class Vector3;

	class UISlider : public UIElement
	{
	public:
		UISlider(std::string overlayName, std::string imageName, int y, int left, int right);
		virtual ~UISlider();

		double getRelativePos();

		/// <summary>
		/// Determines if the element needs to update their position in the transform
		/// </summary>
		/// <returns></returns>
		bool getNeedsSync();

		void setNeedsSync(bool newState);

		void updatePosition(Vector3 newPosition);

		void updateSize(float scale);

	private:
		InputManager* inputMan;

		Rectangle inputArea;

		int leftLimit, rightLimit;
		int initialDistance;
		int distance;

		bool pressed = false;
		bool positionNeedsSync = false;
	};
}
#endif // UISLIDER_H