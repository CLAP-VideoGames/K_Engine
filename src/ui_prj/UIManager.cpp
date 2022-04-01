#include "UIManager.h"
#include "UiElement.h"

#include <iostream>
#include <string>

#include <render_prj/RenderManager.h>
#include <OgreOverlaySystem.h>
#include <OgreSceneManager.h>
#include <OgreImage.h>

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

            instance.get()->overSystem = new Ogre::OverlaySystem();

            K_Engine::RenderManager::GetInstance()->getSceneManager()
                ->addRenderQueueListener(instance.get()->overSystem);

        }
        catch (const std::exception&) {
            return false;
        }

        return true;
    }

    void UIManager::debug()
    {
        addUiElement("TextArea");
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