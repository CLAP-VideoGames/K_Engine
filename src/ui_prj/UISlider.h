#pragma once
#include "UiElement.h"
#include "Rectangle.h"

namespace K_Engine {
	class InputManager;

	class UiSlider : public UiElement
	{
	public:
		UiSlider(std::string overlayName);
		~UiSlider();

		void setProgress(float prog);
		void setMaxProgress(float maximum);

		float getProgress();

		void update();

	private:

		//Starts full progresion
		float progresion = 100;

		float maximumProgresion = 100;

		InputManager* inputMan;

		Rectangle inputArea;
	};
}
