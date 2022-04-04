#pragma once
#include "UiElement.h"

namespace K_Engine {
	
	class UiImage : public UiElement
	{
	public:
		UiImage(std::string overlayName, std::string imageName);
		~UiImage();

		void changeMaterial(std::string newImageName);
	};
}
