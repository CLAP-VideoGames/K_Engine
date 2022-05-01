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

    UIElement* UIManager::getNextFocusDown(UIElement* focus, int offset)
    {
        if (notCeguiElements.size() == 0)
            return nullptr;

        if (notCeguiElements.size() > 1) {
            int lesserHeight = 10000;
            
            UIElement* topElement = nullptr;
            int closestDownPosition = 10000;
            UIElement* closestDownElement = nullptr;

            std::pair<int, int> focusPosition = focus->getPosition();

            for (UIElement* actualElement : notCeguiElements) {
                if (actualElement->isVisible() && actualElement->getOverlayName() != focus->getOverlayName() &&
                    actualElement->getPosition().second != focus->getPosition().second + offset/2 && actualElement->getIsInteractive()) {
                    std::pair<int, int> elementPosition = actualElement->getPosition();
                    if (lesserHeight > elementPosition.second) {
                        lesserHeight = elementPosition.second;
                        topElement = actualElement;
                    }

                    if (elementPosition.second > focusPosition.second) {
                        if (closestDownPosition > elementPosition.second) {
                            closestDownPosition = elementPosition.second;
                            closestDownElement = actualElement;
                        }
                    }
                    
                }
            }

            if (closestDownElement == nullptr)
                return topElement;
            else
                return closestDownElement;
        }

        return nullptr;
    }

    UIElement* UIManager::getNextFocusUp(UIElement* focus, int offset)
    {
        if (notCeguiElements.size() == 0)
            return nullptr;

        if (notCeguiElements.size() > 1) {
            int greaterHeight = -10000;

            UIElement* bottomElement = nullptr;
            int closestTopPosition = -10000;
            UIElement* closestTopElement = nullptr;

            std::pair<int, int> focusPosition = focus->getPosition();

            for (UIElement* actualElement : notCeguiElements) {
                if (actualElement->isVisible() && actualElement->getOverlayName() != focus->getOverlayName() &&
                    actualElement->getPosition().second != focus->getPosition().second - offset / 2 && actualElement->getIsInteractive()) {
                    std::pair<int, int> elementPosition = actualElement->getPosition();
                    if (greaterHeight < elementPosition.second) {
                        greaterHeight = elementPosition.second;
                        bottomElement = actualElement;
                    }

                    if (elementPosition.second < focusPosition.second) {
                        if (closestTopPosition < elementPosition.second) {
                            closestTopPosition = elementPosition.second;
                            closestTopElement = actualElement;
                        }
                    }

                }
            }

            if (closestTopElement == nullptr)
                return bottomElement;
            else
                return closestTopElement;
        }

        return nullptr;
    }

    UIElement* UIManager::getNextFocusLeft(UIElement* focus, int offset)
    {
        if (notCeguiElements.size() == 0)
            return nullptr;

        if (notCeguiElements.size() > 1) {
            int greaterWidth = -10000;

            UIElement* rightestElement = nullptr;
            int closestLeftPosition = -10000;
            UIElement* closestLeftElement = nullptr;

            std::pair<int, int> focusPosition = focus->getPosition();

            for (UIElement* actualElement : notCeguiElements) {
                if (actualElement->isVisible() && actualElement->getOverlayName() != focus->getOverlayName() &&
                    actualElement->getPosition().first != focus->getPosition().first - offset / 2 && actualElement->getIsInteractive()) {
                    std::pair<int, int> elementPosition = actualElement->getPosition();
                    if (greaterWidth < elementPosition.first) {
                        greaterWidth = elementPosition.first;
                        rightestElement = actualElement;
                    }

                    if (elementPosition.first < focusPosition.first) {
                        if (closestLeftPosition < elementPosition.first) {
                            closestLeftPosition = elementPosition.first;
                            closestLeftElement = actualElement;
                        }
                    }

                }
            }

            if (closestLeftElement == nullptr)
                return rightestElement;
            else
                return closestLeftElement;
        }

        return nullptr;
    }

    UIElement* UIManager::getNextFocusRight(UIElement* focus, int offset)
    {
        if (notCeguiElements.size() == 0)
            return nullptr;

        if (notCeguiElements.size() > 1) {
            int lesserWidth = 10000;

            UIElement* leftestElement = nullptr;
            int closestRightPosition = 10000;
            UIElement* closestRightElement = nullptr;

            std::pair<int, int> focusPosition = focus->getPosition();

            for (UIElement* actualElement : notCeguiElements) {
                if (actualElement->isVisible() && actualElement->getOverlayName() != focus->getOverlayName() &&
                    actualElement->getPosition().first != focus->getPosition().first + offset / 2 && actualElement->getIsInteractive()) {
                    std::pair<int, int> elementPosition = actualElement->getPosition();
                    if (lesserWidth > elementPosition.first) {
                        lesserWidth = elementPosition.first;
                        leftestElement = actualElement;
                    }

                    if (elementPosition.first > focusPosition.first) {
                        if (closestRightPosition > elementPosition.first) {
                            closestRightPosition = elementPosition.first;
                            closestRightElement = actualElement;
                        }
                    }
                }
            }

            if (closestRightElement == nullptr)
                return leftestElement;
            else
                return closestRightElement;
        }

        return nullptr;
    }

    void UIManager::closeOverlaySystem()
    {
        delete instance.get()->overSystem_; instance.get()->overSystem_ = nullptr;
    }
}