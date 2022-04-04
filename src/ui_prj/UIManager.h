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
	class UiButton;
	class UiScrollBar;

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

		/// <summary>
		/// Adds a button to your scene with its default values and the specified image
		/// </summary>
		/// <param name="overlayName">This is the name ogre will recognice you elemtn</param>
		/// <param name="imageName"> This is the name of the material that will appear for the button</param>
		/// <returns></returns>
		UiButton* addButton(std::string overlayName, std::string imageName);

		/// <summary>
		/// Adds a scrollbar to your scene with its default values and the specified limits
		/// </summary>
		/// <param name="overlayName">This is the name ogre will recognice you elemtn</param>
		/// <param name="upper"> This is the upper limit that the scrollbar will take in consideration when moving</param>
		/// <param name="lower"> This is the lower limit that the scrollbar will take in consideration when moving</param>
		/// <returns></returns>
		UiScrollBar* addScrollBar(std::string overlayName, int upper, int lower);

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