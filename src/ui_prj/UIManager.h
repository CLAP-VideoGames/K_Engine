#pragma once
#ifndef UIMANAGER_H
#define UIMANAGER_H

#include <memory>
#include <string>
#include <vector>

namespace Ogre {
	class OverlaySystem;
	class OverlayManager;
}

namespace K_Engine {
	class UIElement;
	class RenderManager;

	class  __declspec(dllexport) UIManager {
	public:
		UIManager();
		~UIManager();

		static UIManager* GetInstance();

		static bool Init();
		static bool Shutdown();

		void update();

		// generic widget add
		template<typename T, typename ...Ts>
		T* addWidget(std::string overlayName, std::string srcName, Ts &&... args) {
			T* widget = new T(overlayName, srcName, args...);
			notCeguiElements.push_back(widget);
			return widget;
		}

		void cleanElements();

	private:
		static std::unique_ptr<UIManager> instance;

		std::vector<UIElement*> notCeguiElements;

		Ogre::OverlaySystem* overSystem_;
		Ogre::OverlayManager* overlayMngr_;

		RenderManager* renderMan;

		void initOverlaySystem();
		void preloadingScreen();

		void closeOverlaySystem();
	};
}
#endif // UIMANAGER_H