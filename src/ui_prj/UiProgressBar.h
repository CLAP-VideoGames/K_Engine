#pragma once
#ifndef UIPROGRESSBAR_H
#define UIPROGRESSBAR_H
#include "UiElement.h"

namespace K_Engine {

	class UiProgressBar : public UiElement
	{
	public:

		UiProgressBar(std::string overlayName, std::string imageName);
		~UiProgressBar();

		void setProgress(float prog);
		void setMaxProgress(float maximum);

		float getProgress();

	private:

		//Starts full progresion
		float progresion = 100;

		float maximumProgresion = 100;

	};
}


#endif