#pragma once
#ifndef UIMANAGER_H
#define UIMANAGER_H
#include <memory>
#include <string>
#include <vector>

class UiElement;

namespace Ogre {
	class OverlaySystem;
	class Image;
}

namespace K_Engine {
	class UIManager {
	public:
		UIManager();
		~UIManager();

		static UIManager* GetInstance();

		static bool Init(std::string n);
		static bool Shutdown();

		void debug();

		void update();

		UiElement* addUiElement(std::string elementType);

	private:
		static std::unique_ptr<UIManager> instance;
		std::string name;

		std::vector<UiElement*> ceguiElements;

		Ogre::OverlaySystem* overSystem;

		void cleanElements();
	};
}
#endif // UIMANAGER_H