#pragma once
#ifndef UISCROLLBAR_H
#define UISCROLLBAR_H

#include <ui_prj/Rectangle.h>
#include <ui_prj/UiElement.h>

namespace K_Engine {
	class InputManager;
	class Vector3;

	class UiScrollBar : public UiElement
	{
	public:
		UiScrollBar(std::string overlayName, std::string imageName, int upper, int lower);
		~UiScrollBar();

		virtual void update();

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

		int upperLimit, lowerLimit;
		int initialDistance;
		int distance;

		bool pressed = false;
		bool positionNeedsSync = false;
	};
}
#endif // UISCROLLBAR_H