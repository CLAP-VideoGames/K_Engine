#pragma once
#ifndef UIMANAGER_H
#define UIMANAGER_H
#include <memory>
#include <string>
#include <vector>


namespace Ogre {
	class Image;
	class OverlaySystem;
	class OverlayManager;
	class Overlay;
}

namespace K_Engine {

	class UiElement;
	class UiProgressBar;
	class UiText;
	class UiImage;

	class  __declspec(dllexport) UIManager {
	public:

		UIManager();
		~UIManager();

		static UIManager* GetInstance();

		static bool Init(std::string n);
		static bool Shutdown();

		void debug();

		void update();

		/// <summary>
		/// Adds a progressBar to your scene with its default values
		/// </summary>
		/// <param name="overlayName">This is the name ogre will recognice you elemtn</param>
		/// <returns></returns>
		UiProgressBar* addProgressBar(std::string overlayName);

		UiText* addText(std::string overlayName, std::string text);

		UiImage* addImage(std::string overlayName, std::string imageName);

	private:
		static std::unique_ptr<UIManager> instance;
		std::string name;

		std::vector<UiElement*> ceguiElements;

		Ogre::OverlaySystem* overSystem_;
		Ogre::OverlayManager* oveMngr_;
		Ogre::Overlay* overlayElement_;


		void cleanElements();
	};
}
#endif // UIMANAGER_H