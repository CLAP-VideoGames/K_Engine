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

	class UIElement;
	class UIProgressBar;
	class UIText;
	class UIImage;
	class UIButton;
	class UIScrollBar;
	class UISlider;

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
		UIProgressBar* addProgressBar(std::string overlayName, std::string imageName, int x, int y, int orgWidth, int orgHeight);

		UIText* addText(std::string overlayName, std::string text);

		UIImage* addImage(std::string overlayName, std::string imageName);

		/// <summary>
		/// Adds a button to your scene with its default values and the specified image
		/// </summary>
		/// <param name="overlayName">This is the name ogre will recognice you elemtn</param>
		/// <param name="imageName"> This is the name of the material that will appear for the button</param>
		/// /// <param name="hoverImageName">This is the name of the material that will appear when the button is hovered</param>
		/// <param name="pressedImageName"> This is the name of the material that will appear when the button is pressed</param>
		/// <returns></returns>
		UIButton* addButton(std::string overlayName, std::string imageName, std::string hoverImageName, std::string pressedImageName);

		/// <summary>
		/// Adds a scrollbar to your scene with its default values and the specified limits
		/// </summary>
		/// <param name="overlayName">This is the name ogre will recognice you elemtn</param>
		/// <param name="imageName">This is the name of the image used for the scroll bar</param>
		/// <param name="upper"> This is the upper limit that the scrollbar will take in consideration when moving</param>
		/// <param name="lower"> This is the lower limit that the scrollbar will take in consideration when moving</param>
		/// <returns></returns>
		UIScrollBar* addScrollBar(std::string overlayName, std::string imageName, int x, int upper, int lower);

		UISlider* addSlider(std::string overlayName, std::string imageName, int y, int left, int right);

	private:
		static std::unique_ptr<UIManager> instance;

		std::string name;

		std::vector<UIElement*> notCeguiElements;

		Ogre::OverlaySystem* overSystem_;
		Ogre::OverlayManager* overlayMngr_;

		void cleanElements();
	};
}
#endif // UIMANAGER_H