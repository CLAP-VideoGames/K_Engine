#pragma once
#ifndef UIPROGRESSBAR_H
#define UIPROGRESSBAR_H

#include <ui_prj/UiElement.h>

namespace K_Engine {

	class UIProgressBar : public UIElement
	{
	public:
		UIProgressBar(std::string overlayName, std::string imageName, int x, int y, int orgWidth, int orgHeight);
		virtual ~UIProgressBar();

		void setProgress(float prog);
		void setMaxProgress(float maximum);

		float getProgress();

	private:

		std::pair<int, int> originalSize;

		//Starts full progresion
		float progresion = 100;

		float maximumProgresion = 100;

	};
}
#endif // UIPROGRESS_H