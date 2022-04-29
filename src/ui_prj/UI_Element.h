#pragma once
#ifndef UIELEMENT_H
#define UIELEMENT_H

#include <string>

namespace Ogre {
	class Overlay;
	class OverlayContainer;
	class OverlayManager;
}

#define DEFAULT_WIDTH 500
#define DEFAULT_HEIGHT 150

#define DEFAULT_LEFT 0
#define DEFAULT_TOP 0

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
		UIElement();
		virtual ~UIElement();

		void show(); // Shows the overlay
		void hide(); // Hides the overlay

		void setMaterial(std::string const& materialName);

		// Virtual because some elements dont use the generic class OverlayContainer
		// for example: TextArea, so we need to use other kind of element 
		virtual void setPosition(int x, int y);
		virtual void setSize(int w, int h);

		void setTop(int topValue);
		void setLeft(int leftValue);

		void setWidth(int widthValue);
		void setHeight(int heightValue);
		
		// Pixels make setPosition and setDimesions work with Pixels
		// and WindowRelative makest it relative to the window
		void setMetrics(Metrics m);

		// Bigger z is closer to the camera
		void setRenderOrder(int z);
		
		std::pair<int, int> getPosition();
		virtual std::pair<int, int> getSize();

	protected:
		static int numOverlayElems;

		Ogre::OverlayManager* overlayMan_;

		Ogre::Overlay* overlay_;
		Ogre::OverlayContainer* overlayElement_;
	};
}
#endif // UIELEMENT_H