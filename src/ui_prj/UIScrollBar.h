#pragma once

#ifndef _UI_SCROLLBAR_H
#define _UI_SCROLLBAR_H
#include "UIComponent.h"

class UIScrollbar :public UIComponent
{
private:
	float value;
public:
	UIScrollbar(CEGUI::WindowManager* winMngr, CEGUI::DefaultWindow* mRoot, std::string& schemeName, Vector2 pos_, Vector2 size_, std::string name_, float v);
	virtual ~UIScrollbar() {};
};

#endif