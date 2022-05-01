#pragma once
#ifndef UIIMAGE_H
#define UIIMAGE_H

#include <ui_prj/UIElement.h>

namespace K_Engine {
	class UIImage : public UIElement
	{
	public:
		UIImage(std::string overlayName, std::string imageName);
		virtual ~UIImage();

		void setDimensions(int width, int height);
	};
}
#endif // UIIMAGE_H