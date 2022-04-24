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
            for (size_t i = 0; i < instance.get()->notCeguiElements.size(); i++)
                delete instance.get()->notCeguiElements[i];
            instance.get()->notCeguiElements.clear();

            delete instance.get()->overSystem_; instance.get()->overSystem_ = nullptr;

            instance.reset(nullptr);
        }
        catch (Ogre::Exception& e) {
            return K_Engine::LogManager::GetInstance()->addLog(K_Engine::LogType::FATAL, e.getFullDescription());
        }

        return K_Engine::LogManager::GetInstance()->addLog(K_Engine::LogType::INFO, "UI manager shutdown success");
    }

    void UIManager::update()
    {
        for (int i = 0; i < notCeguiElements.size(); i++)
            notCeguiElements[i]->update();
    }

    UIProgressBar* UIManager::addProgressBar(std::string overlayName, std::string imageName, int x, int y, int orgWidth, int orgHeight)
    {
        UIProgressBar* p = new UIProgressBar(overlayName, imageName, x, y, orgWidth, orgHeight);

        notCeguiElements.push_back(p);

        return p;
    }

    UIText* UIManager::addText(std::string overlayName, std::string text)
    {
        UIText* t = new UIText(overlayName, text);

        notCeguiElements.push_back(t);

        return t;
    }

    UIImage* UIManager::addImage(std::string overlayName, std::string imageName)
    {
        UIImage* i = new UIImage(overlayName, imageName);

        notCeguiElements.push_back(i);

        return i;
    }

    UIButton* UIManager::addButton(std::string overlayName, std::string imageName, std::string hoverImageName, std::string pressedImageName)
    {
        UIButton* b = new UIButton(overlayName, imageName, hoverImageName, pressedImageName);

        notCeguiElements.push_back(b);

        return b;
    }

    UIScrollBar* UIManager::addScrollBar(std::string overlayName, std::string imageName, int x, int upper, int lower) {
        UIScrollBar* s = new UIScrollBar(overlayName, imageName, x, upper, lower);
        
        notCeguiElements.push_back(s);

        return s;
    }

    UISlider* UIManager::addSlider(std::string overlayName, std::string imageName, int y, int left, int right) {
        UISlider* s = new UISlider(overlayName, imageName, y, left, right);

        notCeguiElements.push_back(s);

        return s;
    }

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
        for (UIElement* c : notCeguiElements) 
            delete c;
    }
}