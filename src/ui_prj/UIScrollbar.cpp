#include "UiScrollBar.h"
#include <OgreOverlayContainer.h>
#include <OgreOverlayManager.h>
#include <OgreTextAreaOverlayElement.h>
#include <OgreOverlay.h>
#include <input_prj/InputManager.h>
#include <iostream>

namespace K_Engine {

    UiScrollBar::UiScrollBar(std::string overlayName, int upper, int lower) : UiElement(Ogre::OverlayManager::getSingletonPtr())
    {
        //Initialization of everything that ogre needs to show something
        //Default settings
        element_ = static_cast<Ogre::OverlayContainer*>(
            oveMngr_->createOverlayElement("Panel", "ScrollBar"));
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

        inputMan = K_Engine::InputManager::GetInstance();

        //Setup the movement limits of the scrollbar
        upperLimit = upper;
        lowerLimit = lower;

        //Setup default size relative to the total distance
        distance = lower - upper;
        if (distance / 10 > 0) {
            setSize(50, distance / 10);
        }
        else setSize(50, distance);

        //Setup the input area rectangle
        inputArea.h = size.second;
        inputArea.w = size.first;
        inputArea.x = position.first;
        inputArea.y = position.second;
    }

    UiScrollBar::~UiScrollBar()
    {

    }

    //Returns the percentage of the scrollbar that is left above the scrollbar itself
    //this means that 100 is when the bar is on top and the closer it gets to 0 the lower it is.
    double UiScrollBar::getRelativePos() {
        return (((double)distance - (double)getPosition().second) / (double)distance) * 100;
    }

    //Sets the position according to mouse input and pos
    void UiScrollBar::update() {
        if (inputMan->getLeftMouseButtonPressed())
        {
            Point pointer;
            auto pointPos = inputMan->getMousePos();
            pointer.x = pointPos.first;
            pointer.y = pointPos.second;

            if (PointInRect(&pointer, &inputArea)) {
                if (getPosition().second > upperLimit && getPosition().second < lowerLimit) {
                    setPosition(pointer.x, pointer.y);
                }
            }
        }
    }
}