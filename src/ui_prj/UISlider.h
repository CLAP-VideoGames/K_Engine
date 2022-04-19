#pragma once
#ifndef UISLIDER_H
#define UISLIDER_H

#include <ui_prj/Rectangle.h>
#include <ui_prj/UiElement.h>

namespace K_Engine {
	class InputManager;

	class UISlider : public UIElement
	{
	public:
		UISlider(std::string overlayName);
		virtual ~UISlider();

		void setProgress(float prog);
		void setMaxProgress(float maximum);

		float getProgress();

		virtual void update();

	private:
		//Starts full progresion
		float progresion = 100;

		float maximumProgresion = 100;

		InputManager* inputMan;

		Rectangle inputArea;
	};
}
#endif // UISLIDER_H