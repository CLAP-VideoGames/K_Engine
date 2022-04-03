#include "UiButton.h"
#include <OgreOverlayContainer.h>
#include <OgreOverlayManager.h>
#include <OgreTextAreaOverlayElement.h>
#include <OgreOverlay.h>
#include <input_prj/InputManager.h>
#include <iostream>

namespace K_Engine {

    UiButton::UiButton(std::string overlayName, std::string imageName) : UiElement(Ogre::OverlayManager::getSingletonPtr())
    {
        //Initialization of everything that ogre needs to show something
        //Default settings
        element_ = static_cast<Ogre::OverlayContainer*>(
            oveMngr_->createOverlayElement("Panel", "Button"));
        element_->setMetricsMode(Ogre::GMM_PIXELS);
        element_->setPosition(defaultX, defaultY);
        element_->setDimensions(defaultWidth, defaultHeight);

        //DefaultMaterial
        element_->setMaterialName(imageName);

        // Create an overlay, and add the panel
        overlay_ = oveMngr_->create(overlayName);
        overlay_->add2D(element_);

        // Show the overlay
        overlay_->show();

        size = std::pair<int, int>(400, 150);

        inputMan = K_Engine::InputManager::GetInstance();

        inputArea.h = size.second;
        inputArea.w = size.first;
        inputArea.x = position.first;
        inputArea.y = position.second;
    }

    UiButton::~UiButton()
    {

    }

    void UiButton::update() {
        if (inputMan->getLeftMouseButtonPressed())
        {
            Point pointer;
            auto pointPos = inputMan->getMousePos();
            pointer.x = pointPos.first;
            pointer.y = pointPos.second;

            if (PointInRect(&pointer, &inputArea)) {
                //std::cout << "Button Pressed \n";
                pressed_ = true;
                //auto g = K_Engine::LogManager::GetInstance();
                //g->addLog("mecagoenlaputamadredelaputadetumadre", K_Engine::LogManager::info);
            }
            else pressed_ = false;
        }
        else pressed_ = false;
    }
}