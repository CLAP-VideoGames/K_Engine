#include "UIManager.h"
#include "UiElement.h"
#include "UiText.h"
#include "UiProgressBar.h"
#include "UiImage.h"
#include "UiButton.h"
#include "UiScrollBar.h"
#include "UiSlider.h"

#include <iostream>
#include <string>

#include <OgreLogManager.h>
#include <OgreOverlay.h>
#include <OgreOverlaySystem.h>
#include <OgreOverlayManager.h>
#include <OgreImage.h>
#include <OgreSceneManager.h>
#include <OgreOverlayContainer.h>
#include <OgreTextAreaOverlayElement.h>
#include <OgreFontManager.h>

#include <render_prj/RenderManager.h>

#include <log_prj/LogManager.h>

#include <utils_prj/checkML.h>

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
    bool UIManager::Init()
    {
        try {
            instance.reset(new UIManager());

            instance.get()->initOverlaySystem();
            instance.get()->preloadingScreen();
        }
        catch (Ogre::Exception& e) {
            return K_Engine::LogManager::GetInstance()->addLog(K_Engine::LogType::FATAL, e.getFullDescription());
        }

        return K_Engine::LogManager::GetInstance()->addLog(K_Engine::LogType::INFO, "UI manager initialization success");
    }

    /*************************************************************************
        Cleans up resources allocated in the initialiseSample call.
    *************************************************************************/
    bool UIManager::Shutdown()
    {
        try {
            instance.get()->cleanElements();
            instance.get()->closeOverlaySystem();

            instance.reset(nullptr);
        }
        catch (Ogre::Exception& e) {
            return K_Engine::LogManager::GetInstance()->addLog(K_Engine::LogType::FATAL, e.getFullDescription());
        }

        return K_Engine::LogManager::GetInstance()->addLog(K_Engine::LogType::INFO, "UI manager shutdown success");
    }

    void UIManager::update() {};

    void UIManager::initOverlaySystem()
    {
        // Requires initialization of RenderManager first
        instance.get()->overSystem_ = new Ogre::OverlaySystem();
        instance.get()->overlayMngr_ = Ogre::OverlayManager::getSingletonPtr();

        renderMan = K_Engine::RenderManager::GetInstance();
        renderMan->getSceneManager()->addRenderQueueListener(instance.get()->overSystem_);
    }

    void UIManager::preloadingScreen()
    {
        renderMan->locateResources("./preload.cfg");
        UIImage loadScreen("Example", "LoadScreen"); loadScreen.setSize(renderMan->windowWidth(), renderMan->windowHeight());
        renderMan->render();
    }

    void UIManager::cleanElements()
    {
        for (UIElement* uiElem : notCeguiElements) 
            delete uiElem;
        notCeguiElements.clear();
    }

    void UIManager::closeOverlaySystem()
    {
        delete instance.get()->overSystem_; instance.get()->overSystem_ = nullptr;
    }
}