#pragma once
#ifndef UIELEMENT_H
#define UIELEMENT_H

#include <string>

namespace Ogre {
	class Overlay;
	class OverlayContainer;
}

class UiElement
{
public:
	UiElement();
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

	void loadElementType(std::string const& overlayName);

private:

	Ogre::Overlay* overlay;
	
	Ogre::OverlayContainer* element;
};
#endif