#pragma once

#ifndef _UI_SLIDER_H
#define _UI_SLIDER_H
#include "UIComponent.h"

class UISlider :public UIComponent
{
private:
	float value;
public:
	UISlider(CEGUI::WindowManager* winMngr, CEGUI::DefaultWindow* mRoot, std::string& schemeName, Vector2 pos_, Vector2 size_, std::string name_, float v);
	virtual ~UISlider() {};
};

#endif
