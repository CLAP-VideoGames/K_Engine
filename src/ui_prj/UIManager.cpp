#include "UIManager.h"
#include "UiElement.h"
#include "UiText.h"
#include "UiProgressBar.h"
#include "UiImage.h"
#include "UiButton.h"
#include "UiScrollBar.h"

#include <iostream>
#include <string>

#include <render_prj/RenderManager.h>
#include <OgreLogManager.h>

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

            //instance.get()->overSystem_ = new Ogre::OverlaySystem();
            instance.get()->oveMngr_ = Ogre::OverlayManager::getSingletonPtr();
            //K_Engine::RenderManager::GetInstance()->getSceneManager()
            //    ->addRenderQueueListener(instance.get()->overSystem_);

        }
        catch (const std::exception&) {
            return false;
        }

        return true;
    }

    void UIManager::debug()
    {
        //addUiElement("TextArea");

        try
        {
            UiProgressBar* pG = addProgressBar("A");
            notCeguiElements[0]->setPosition(10, 680);
            notCeguiElements[0]->setSize(300, 25);
            pG->setMaterial("GreenDefaultProgressBar");
            pG->setProgress(50);
            pG->setRenderOrder(100);

            UiProgressBar* p = addProgressBar("B");
            notCeguiElements[1]->setPosition(10, 680);
            notCeguiElements[1]->setSize(300, 25);
            p->setMaterial("DefaultProgressBar");
            p->setRenderOrder(50);

            addScrollBar("C", 1, 100);
            notCeguiElements[2]->setRenderOrder(500);


            addText("D", "Fino senhores");
            notCeguiElements[3]->setPosition(135,10);

            addImage("E", "Fino");


            addButton("F", "TestButton");
            notCeguiElements[5]->setPosition(950, 5);
            notCeguiElements[5]->setSize(100, 100);


            //Ogre::OverlayContainer* panel = static_cast<Ogre::OverlayContainer*>(
            //    oveMngr_->createOverlayElement("Panel", "PanelName"));
            //panel->setMetricsMode(Ogre::GMM_PIXELS);
            //panel->setPosition(10, 10);
            //panel->setDimensions(500, 150);
            //panel->setMaterialName("DefaultButton");

            //Ogre::TextAreaOverlayElement* textArea = static_cast<Ogre::TextAreaOverlayElement*>(
            //    oveMngr_->createOverlayElement("TextArea", "TextAreaName"));
            //textArea->setMetricsMode(Ogre::GMM_PIXELS);
            //textArea->setPosition(50, 50);
            //textArea->setDimensions(200, 200);
            //textArea->setCaption("U.C.M : Panda de Simios!");
            //textArea->setCharHeight(40);
            //textArea->setFontName("MyFont");
            //textArea->setColourBottom(Ogre::ColourValue(0.03, 0.05, 0.03));
            //textArea->setColourTop(Ogre::ColourValue(0.9, 0.95, 0.95));

            //// Create an overlay, and add the panel
            //Ogre::Overlay* overlay = oveMngr_->create("OverlayName");
            //overlay->add2D(panel);

            //// Add the text area to the panel
            //panel->addChild(textArea);

            //// Show the overlay
            //overlay->show();

            //addButton("Button", "DefaultButton");
        }
        catch (Ogre::Exception& e) {
            Ogre::LogManager::getSingleton().logMessage("An exception has occured: " + e.getFullDescription() + "\n");
        }
        // Create a text area
    }

    void UIManager::update()
    {
        for (int i = 0; i < notCeguiElements.size(); i++)
            notCeguiElements[i]->update();
    }

    UiProgressBar* UIManager::addProgressBar(std::string overlayName)
    {
        UiProgressBar* p = new UiProgressBar(overlayName);

        notCeguiElements.push_back(p);

        return p;
    }

    UiText* UIManager::addText(std::string overlayName, std::string text)
    {
        UiText* t = new UiText(overlayName, text);

        notCeguiElements.push_back(t);

        return t;
    }

    UiImage* UIManager::addImage(std::string overlayName, std::string imageName)
    {
        UiImage* i = new UiImage(overlayName, imageName);

        notCeguiElements.push_back(i);

        return i;
    }

    UiButton* UIManager::addButton(std::string overlayName, std::string imageName)
    {
        UiButton* b = new UiButton(overlayName, imageName);

        notCeguiElements.push_back(b);

        return b;
    }

    UiScrollBar* UIManager::addScrollBar(std::string overlayName, int upper, int lower) {
        UiScrollBar* s = new UiScrollBar(overlayName, upper, lower);
        
        notCeguiElements.push_back(s);

        return s;
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
        for (UiElement* c : notCeguiElements) {
            delete c;
        }
    }

}