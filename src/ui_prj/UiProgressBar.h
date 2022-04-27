#pragma once
#ifndef UIPROGRESSBAR_H
#define UIPROGRESSBAR_H

#include <ui_prj/UIElement.h>

namespace K_Engine {

	class UIProgressBar : public UIElement
	{
	public:
		UIProgressBar(std::string overlayName, std::string imageName, int x, int y, int orgWidth, int orgHeight);
		virtual ~UIProgressBar();
	};
}
#endif // UIPROGRESS_H