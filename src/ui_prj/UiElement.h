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

	enum Metrics{Pixels, WindowRelative};
	/// <summary>
	/// Parent class for every UiElement like button or Text,
	/// Default metrics is WindowRelative
	/// </summary>
	
	class UiElement
	{
	public:
		UiElement(Ogre::OverlayManager* man);
		~UiElement();

		/// <summary>
		/// Shows the overlay
		/// </summary>
		void show();

		/// <summary>
		/// Hides the overlay
		/// </summary>
		void hide();

		void setMaterial(std::string const& materialName);

		std::pair<int, int> getPosition();

		std::pair<int, int> getSize();

		//Virtual because some elements dont use the generic class OverlayContainer
		// for example: TextArea, so we need to use othe kind of element 
		virtual void setPosition(int x, int y);
		virtual void setSize(int w, int h);


		/// <summary>
		/// Pixels make setPosition and setDimesions work with PIxels
		/// and WindowRelative makest it relative to the window
		/// </summary>
		/// <param name="metrics"></param>
		void setMetrics(Metrics m);

		//For input based UI
		virtual void update() {};

		/// <summary>
		/// Bigger z is closer to the camera
		/// </summary>
		/// <param name="z"></param>
		void setRenderOrder(int z);

	protected:


		Ogre::Overlay* overlay_;
		Ogre::OverlayContainer* element_;
		Ogre::OverlayManager* oveMngr_;

		int defaultWidth = 500;
		int defaultHeight = 150;

		int defaultX = 10;
		int defaultY = 10;

		//Information for the user
		std::pair<int, int> size;
		std::pair<int, int> position;

	};
}
#endif