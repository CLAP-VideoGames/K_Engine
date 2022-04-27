#pragma once
#ifndef UIELEMENT_H
#define UIELEMENT_H

#include <string>

namespace Ogre {
	class Overlay;
	class OverlayContainer;
	class OverlayManager;
}

namespace K_Engine {
	enum Metrics {
		PIXELS, 
		WINDOW_RELATIVE
	};

	/// <summary>
	/// Parent class for every UiElement like button or Text,
	/// Default metrics is WindowRelative
	/// </summary>
	class UIElement
	{
	public:
		UIElement(Ogre::OverlayManager* man);

		virtual ~UIElement();

		void show(); // Shows the overlay
		void hide(); // Hides the overlay

		void setMaterial(std::string const& materialName);

		// Virtual because some elements dont use the generic class OverlayContainer
		// for example: TextArea, so we need to use othe kind of element 
		virtual void setPosition(int x, int y);
		virtual void setSize(int w, int h);

		void setTop(int topValue);
		void setLeft(int leftValue);
		
		/// <summary>
		/// Pixels make setPosition and setDimesions work with Pixels
		/// and WindowRelative makest it relative to the window
		/// </summary>
		/// <param name="metrics"></param>
		void setMetrics(Metrics m);

		/// <summary>
		/// Bigger z is closer to the camera
		/// </summary>
		/// <param name="z"></param>
		void setRenderOrder(int z);
		
		std::pair<int, int> getPosition();
		std::pair<int, int> getSize();

		int getLeft();
		int getTop();

		int getHeight();
		int getWidth();

	protected:
		Ogre::OverlayManager* overlayMan_;

		Ogre::Overlay* overlay_;
		Ogre::OverlayContainer* element_;

		int defaultWidth = 500;
		int defaultHeight = 150;

		int defaultX = 0;
		int defaultY = 0;

		//Information for the user
		std::pair<int, int> size;
		std::pair<int, int> position;
	};
}
#endif // UIELEMENT_H