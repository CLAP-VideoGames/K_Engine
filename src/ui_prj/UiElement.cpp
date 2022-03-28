#include "UiElement.h"
#include <OgreOverlay.h>
#include <OgreOverlayContainer.h>
#include <render_prj/RenderManager.h>
#include <OgreRenderTarget.h>
#include <OgreOverlayManager.h>
#include <OgreTextAreaOverlayElement.h>

UiElement::UiElement()
{
	overlay = nullptr;
}

UiElement::~UiElement()
{

}

void UiElement::show()
{
	overlay->show();
}

void UiElement::hide()
{
	overlay->hide();
}

std::pair<int, int> UiElement::getPosition()
{
	double x = static_cast<double>(overlay->getChild("")->getLeft());
	double y = static_cast<double>(overlay->getChild("")->getTop());

	Ogre::RenderTarget* wnd = K_Engine::RenderManager::GetInstance()->getRenderWindow();

	std::pair<int, int> windowSize(wnd->getWidth(), wnd->getHeight());
	return std::pair<int, int>((int)(x * windowSize.first), (int)(y * windowSize.second));
}

std::pair<int, int> UiElement::getSize()
{
	double x = static_cast<double>(overlay->getChild("")->getWidth());
	double y = static_cast<double>(overlay->getChild("")->getHeight());

	Ogre::RenderTarget* wnd = K_Engine::RenderManager::GetInstance()->getRenderWindow();

	std::pair<int, int> windowSize(wnd->getWidth(), wnd->getHeight());
	return std::pair<int, int>((int)(x * windowSize.first), (int)(y * windowSize.second));
}

void UiElement::loadElementType(std::string const& overlayName)
{
	Ogre::Overlay* overlay = Ogre::OverlayManager::getSingletonPtr()->create(overlayName);

	Ogre::TextAreaOverlayElement* panel = static_cast<Ogre::TextAreaOverlayElement*>(//Type		ID
		Ogre::OverlayManager::getSingletonPtr()->createOverlayElement(overlayName, "MotoMoto"));

	panel->setPosition(0.1, 0.5);
	panel->setDimensions(0.5, 0.5);
	panel->setCaption(Ogre::DisplayString("Hola bo dia"));

	//panel->setFontName("Jura-Light");


	//// Show the overlay
	overlay->show();
}


