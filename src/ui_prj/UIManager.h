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
		/// <param name="imageName">This is the name of the image used for the progress bar</param>
		/// <returns></returns>
		UiProgressBar* addProgressBar(std::string overlayName, std::string imageName);

		UiText* addText(std::string overlayName, std::string text);

		UiImage* addImage(std::string overlayName, std::string imageName);

		/// <summary>
		/// Adds a button to your scene with its default values and the specified image
		/// </summary>
		/// <param name="overlayName">This is the name ogre will recognice you elemtn</param>
		/// <param name="imageName"> This is the name of the material that will appear for the button</param>
		/// /// <param name="hoverImageName">This is the name of the material that will appear when the button is hovered</param>
		/// <param name="pressedImageName"> This is the name of the material that will appear when the button is pressed</param>
		/// <returns></returns>
		UiButton* addButton(std::string overlayName, std::string imageName, std::string hoverImageName, std::string pressedImageName);

		/// <summary>
		/// Adds a scrollbar to your scene with its default values and the specified limits
		/// </summary>
		/// <param name="overlayName">This is the name ogre will recognice you elemtn</param>
		/// <param name="imageName">This is the name of the image used for the scroll bar</param>
		/// <param name="upper"> This is the upper limit that the scrollbar will take in consideration when moving</param>
		/// <param name="lower"> This is the lower limit that the scrollbar will take in consideration when moving</param>
		/// <returns></returns>
		UiScrollBar* addScrollBar(std::string overlayName, std::string imageName, int upper, int lower);

	private:
		static std::unique_ptr<UIManager> instance;
		std::string name;

		std::vector<UiElement*> notCeguiElements;

		Ogre::OverlaySystem* overSystem_;
		Ogre::OverlayManager* oveMngr_;
		Ogre::Overlay* overlayElement_;


		void cleanElements();
	};
}
#endif // UIMANAGER_H