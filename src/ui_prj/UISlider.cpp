#include "UiSlider.h"
//#include "log_prj/LogManager.h"
#include <OgreOverlayContainer.h>
#include <OgreOverlayManager.h>
#include <OgreTextAreaOverlayElement.h>
#include <OgreOverlay.h>
#include <input_prj/InputManager.h>
#include <iostream>

namespace K_Engine {

    static int numberOfBars = 0;

    UiSlider::UiSlider(std::string overlayName) : UiElement(Ogre::OverlayManager::getSingletonPtr())
    {
        std::string elemtnNumber = std::to_string(numberOfBars);

        //Initialization of everything that ogre needs to show something
        //Default settings
        element_ = static_cast<Ogre::OverlayContainer*>(
            oveMngr_->createOverlayElement("Panel", "Slider" + elemtnNumber));
        element_->setMetricsMode(Ogre::GMM_PIXELS);
        element_->setPosition(defaultX, defaultY);
        element_->setDimensions(defaultWidth, defaultHeight);

        //DefaultMaterial
        element_->setMaterialName("DefaultButton");

        // Create an overlay, and add the panel
        overlay_ = oveMngr_->create(overlayName);
        overlay_->add2D(element_);

        // Show the overlay
        overlay_->show();

        numberOfBars++;

        size = std::pair<int, int>(500, 150);

        inputMan = K_Engine::InputManager::GetInstance();
        
        inputArea.h = size.second;
        inputArea.w = size.first;
        inputArea.x = position.first;
        inputArea.y = position.second;
    }

    UiSlider::~UiSlider()
    {

    }

    void UiSlider::setProgress(float prog)
    {
        if (prog <= maximumProgresion)  progresion = prog;
        else progresion = maximumProgresion;


        std::pair<int, int> oldSize = getSize();

        setSize(oldSize.first * (prog / maximumProgresion), oldSize.second);
    }

    void UiSlider::setMaxProgress(float maximum)
    {
        maximumProgresion = maximum;
    }

    float UiSlider::getProgress()
    {
        return progresion;
    }

    void UiSlider::update() {
        Point pointer;
        auto pointPos = inputMan->getMousePos();
        pointer.x = pointPos.first;
        pointer.y = pointPos.second;
        

        if (PointInRectangle(&pointer, &inputArea)) {
            std::cout << "A";
            //auto g = K_Engine::LogManager::GetInstance();
            //g->addLog("mecagoenlaputamadredelaputadetumadre", K_Engine::LogManager::info);
        }

    }
}
