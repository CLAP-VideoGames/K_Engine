#pragma once
#ifndef UIELEMENT_H
#define UIELEMENT_H

#include <string>

namespace Ogre {
	class Overlay;
	class OverlayContainer;
	class OverlayManager;
}

#define DEFAULT_WIDTH 0.2
#define DEFAULT_HEIGHT 0.2

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
		virtual void setPosition(double x, double y);
		virtual void setSize(double w, double h);

		virtual void setTop(double topValue);
		virtual void setLeft(double leftValue);

		virtual void setWidth(double widthValue);
		virtual void setHeight(double heightValue);
		
		// Pixels make setPosition and setDimesions work with Pixels
		// and WindowRelative makest it relative to the window
		virtual void setMetrics(Metrics m);

		// Bigger z is closer to the camera
		void setRenderOrder(int z);
		
		virtual std::pair<double, double> getPosition();
		virtual std::pair<double, double> getSize();

		std::string getOverlayName();
		bool isVisible();

		void setInteractive(bool isInteractive);
		void setFocusNow(bool isFocusNow);

		bool getIsInteractive();
		bool getIsFocusNow();

	protected:
		static int numOverlayElems;

		Ogre::OverlayManager* overlayMan_;

		Ogre::Overlay* overlay_;
		Ogre::OverlayContainer* overlayElement_;

		bool isInteractive_;
		bool isFocusNow_;
	};
}
#endif // UIELEMENT_H