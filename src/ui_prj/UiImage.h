#pragma once
#ifndef UIIMAGE_H
#define UIIMAGE_H

#include <ui_prj/UiElement.h>

namespace K_Engine {
	class UiImage : public UiElement
	{
	public:
		UiImage(std::string overlayName, std::string imageName);
		virtual ~UiImage();

		void changeMaterial(std::string newImageName);
	};
}
#endif // UIIMAGE_H