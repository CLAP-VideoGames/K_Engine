#include "UIManager.h"
#include "UiElement.h"

#include <iostream>
#include <string>

#include <render_prj/RenderManager.h>
#include <OgreOverlaySystem.h>
#include <OgreOverlayManager.h>
#include <OgreSceneManager.h>
#include <OgreImage.h>
#include <OgreOverlay.h>
#include <OgreOverlayContainer.h>
#include <OgreTextAreaOverlayElement.h>
#include <OgreFontManager.h>

using namespace std;

namespace K_Engine {
    std::unique_ptr<UIManager> UIManager::instance = nullptr;

    UIManager::UIManager() = default;

    UIManager::~UIManager() = default;

    UIManager* UIManager::GetInstance() {
        return instance.get();
    }

    /*************************************************************************
        specific initialisation goes here.
    *************************************************************************/
    bool UIManager::Init(std::string n)
    {
        try {
            instance.reset(new UIManager());

            instance.get()->name = n;

            instance.get()->overSystem_ = new Ogre::OverlaySystem();
            instance.get()->oveMngr_ = Ogre::OverlayManager::getSingletonPtr();
            K_Engine::RenderManager::GetInstance()->getSceneManager()
                ->addRenderQueueListener(instance.get()->overSystem_);

        }
        catch (const std::exception&) {
            return false;
        }

        return true;
    }

    void UIManager::debug()
    {
        //addUiElement("TextArea");
        // Create an overlay

        Ogre::Overlay* overlay = oveMngr_->create("OverlayName");

        // Create a panel
        Ogre::OverlayContainer* panel = static_cast<Ogre::OverlayContainer*>(oveMngr_->createOverlayElement("Panel", "PanelName"));
        panel->setPosition(0.0, 0.0);
        panel->setDimensions(0.1, 0.1);
        panel->setMaterialName("BaseWhite");
        // Add the panel to the overlay
        overlay->add2D(panel);

        // Show the overlay
        overlay->show();

        // Create a panel
        //Ogre::OverlayContainer* panel = static_cast<Ogre::OverlayContainer*>(
        //    oveMngr_->createOverlayElement("Panel", "PanelName"));
        //panel->setMetricsMode(Ogre::GMM_PIXELS);
        //panel->setPosition(10, 10);
        //panel->setDimensions(100, 100);
        ////panel->setMaterialName("MaterialName"); // Optional background material

        //Ogre::FontPtr pFont = Ogre::FontManager::getSingletonPtr()->create("MyFont", "Mission 1 : Deliver Tom");
        //pFont->setType(Ogre::FT_TRUETYPE);
        //pFont->setSource("batang.ttf");
        //pFont->setTrueTypeSize(16);
        //pFont->load();

        //// Create a text area
        //Ogre::TextAreaOverlayElement* textArea = static_cast<Ogre::TextAreaOverlayElement*>(
        //    oveMngr_->createOverlayElement("TextArea", "TextAreaName"));
        //textArea->setMetricsMode(Ogre::GMM_PIXELS);
        //textArea->setPosition(0, 0);
        //textArea->setDimensions(100, 100);
        //textArea->setCaption("Hello, World!");
        //textArea->setCharHeight(16);
        //textArea->setFontName("MyFont");
        //textArea->setColourBottom(Ogre::ColourValue(0.3, 0.5, 0.3));
        //textArea->setColourTop(Ogre::ColourValue(0.5, 0.7, 0.5));

        //// Create an overlay, and add the panel
        //Ogre::Overlay* overlay = oveMngr_->create("OverlayName");
        //overlay->add2D(panel);

        //// Add the text area to the panel
        //panel->addChild(textArea);

        //// Show the overlay
        //overlay->show();
    }

    void UIManager::update()
    {
        
        
    }

    UiElement* UIManager::addUiElement(std::string elementType)
    {
        UiElement* newElement = new UiElement();

        newElement->loadElementType(elementType);

        ceguiElements.push_back(newElement);

        return newElement;
    }


    /*************************************************************************
        Cleans up resources allocated in the initialiseSample call.
    *************************************************************************/
    bool UIManager::Shutdown()
    {
        try {
            instance.reset(nullptr);

        }
        catch (const std::exception&) {
            return false;
        }

        return true;
    }

    void UIManager::cleanElements()
    {
        for (UiElement* c : ceguiElements) {
            delete c;
        }
    }

}