#include "UiElement.h"
#include <OgreOverlay.h>
#include <OgreOverlayContainer.h>
#include <render_prj/RenderManager.h>
#include <OgreRenderTarget.h>
#include <OgreOverlayManager.h>
#include <OgreTextAreaOverlayElement.h>

UiElement::UiElement()
{
	overlay_ = nullptr;
}

UiElement::~UiElement()
{

}

void UiElement::show()
{
	overlay_->show();
}

void UiElement::hide()
{
	overlay_->hide();
}

std::pair<int, int> UiElement::getPosition()
{
	double x = static_cast<double>(overlay_->getChild("")->getLeft());
	double y = static_cast<double>(overlay_->getChild("")->getTop());

	Ogre::RenderTarget* wnd = K_Engine::RenderManager::GetInstance()->getRenderWindow();

	std::pair<int, int> windowSize(wnd->getWidth(), wnd->getHeight());
	return std::pair<int, int>((int)(x * windowSize.first), (int)(y * windowSize.second));
}

std::pair<int, int> UiElement::getSize()
{
	double x = static_cast<double>(overlay_->getChild("")->getWidth());
	double y = static_cast<double>(overlay_->getChild("")->getHeight());

	Ogre::RenderTarget* wnd = K_Engine::RenderManager::GetInstance()->getRenderWindow();

	std::pair<int, int> windowSize(wnd->getWidth(), wnd->getHeight());
	return std::pair<int, int>((int)(x * windowSize.first), (int)(y * windowSize.second));
}

void UiElement::loadElementType(std::string const& overlayName)
{
	Ogre::Overlay* overlay = Ogre::OverlayManager::getSingletonPtr()->create("WAZAAAAAAAAAAA");
	overlay->setScale(1.0, 1.0);

	//panel->setFontName("DejaVu/SerifCondensedItalic");

	Ogre::OverlayContainer* container = static_cast<Ogre::OverlayContainer*>
		(Ogre::OverlayManager::getSingletonPtr()->createOverlayElement("Panel", "Moto"));
	container->setMetricsMode(Ogre::GMM_PIXELS);
	container->setDimensions(1080.0, 720.0);
	container->setPosition(0.0, 0.0);
	container->show();

	overlay->add2D(container);

	//_textArea = static_cast<Ogre::TextAreaOverlayElement*>(Ogre::OverlayManager::getSingletonPtr()->getOverlayElement(textAreaName));
	Ogre::TextAreaOverlayElement* panel = static_cast<Ogre::TextAreaOverlayElement*>(//Type		ID
		Ogre::OverlayManager::getSingletonPtr()->createOverlayElement(overlayName, "MotoMoto"));
	panel->setPosition(0.1, 0.5);
	panel->setMetricsMode(Ogre::GMM_PIXELS);
	panel->setDimensions(500.0, 500.0);
	panel->setCaption(Ogre::DisplayString("Hola bo dia"));

	container->addChild(panel);

	panel->show();


	overlay->show();
}