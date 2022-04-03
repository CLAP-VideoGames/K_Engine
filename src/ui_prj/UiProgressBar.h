#pragma once
#include "UiElement.h"

class UiProgressBar : public UiElement
{
public:
	UiProgressBar(std::string overlayName);
	~UiProgressBar();

	void setProgress(float prog);
	void setMaxProgress(float maximum);

	float getProgress();

private:
	
	//Starts full progresion
	float progresion = 100;

	float maximumProgresion = 100;

};