#include "UIManager.h"

#include <iostream>
#include <string>

#include <RenderManager.h>
#include <CEGUI/CEGUI.h>
#include <CEGUI/Window.h>
#include <CEGUI/RendererModules/Ogre/Renderer.h>

using namespace CEGUI;
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

            instance.get()->initContext();
            instance.get()->initRoot();


        }
        catch (const std::exception&) {
            return false;
        }

        return true;
    }

    bool UIManager::handleHelloWorldClicked(const CEGUI::EventArgs& args)
    {
        std::cout << "Hello World!" << std::endl;

        return false;
    }

    void UIManager::initContext()
    {

        // CEGUI BOOTSTRAP
        m_renderer = &CEGUI::OgreRenderer::bootstrapSystem(*K_Engine::RenderManager::GetInstance()->getRenderWindow());

        // not sure if this is needed either but fixed a different issue I saw on the forum with no rendering
        //m_CEGUI.setDisplaySize( CEGUI::Size(800,600) );

        guiContext = &CEGUI::System::getSingleton().createGUIContext(m_renderer->getDefaultRenderTarget());

        //Loading the scheme and setting the context
        SchemeManager::getSingleton().createFromFile("TaharezLook.scheme");
        // Set the root window as root of our GUI Context
    }


    void UIManager::initRoot()
    {
        // Now the system is initialised, we can actually create some UI elements, for
        // this first example, a full-screen 'root' window is set as the active GUI
        // sheet, and then a simple frame window will be created and attached to it.

        // All windows and widgets are created via the WindowManager singleton.
        winMgr = WindowManager::getSingletonPtr();

        // Here we create a "DefaultWindow".  This is a native type, that is, it does
        // not have to be loaded via a scheme, it is always available.  One common use
        // for the DefaultWindow is as a generic container for other windows.  Its
        // size defaults to 1.0f x 1.0f using the Relative metrics mode, which means
        // when it is set as the root GUI sheet window, it will cover the entire display.
        // The DefaultWindow does not perform any rendering of its own, so is invisible.
        //
        // Create a DefaultWindow called 'Root'.
        mRoot = (DefaultWindow*)winMgr->createWindow("DefaultWindow", "Root");
        mRoot->setUsingAutoRenderingSurface(true);
        guiContext->setRootWindow(mRoot);
    }

    void UIManager::exampleUI()
    {
       // CEGUI relies on various systems being set-up, so this is what we do
       // here first.
       //
       // The first thing to do is load a CEGUI 'scheme' this is basically a file
       // that groups all the required resources and definitions for a particular
       // skin so they can be loaded / initialised easily
       //
       // So, we use the SchemeManager singleton to load in a scheme that loads the
       // imagery and registers widgets for the TaharezLook skin.  This scheme also
       // loads in a font that gets used as the system default.
       //CEGUI::Window* wnd =  winMgr->loadLayoutFromFile("K_EngineImage.layout");

       FrameWindow* wnd = (FrameWindow*)winMgr->createWindow("TaharezLook/FrameWindow", "Sample Window");
 
       // The next thing we do is to set a default cursor image.  This is
       // not strictly essential, although it is nice to always have a visible
       // indicator if a window or widget does not explicitly set one of its own.
       //
       // The TaharezLook Imageset contains an Image named "MouseArrow" which is
       // the ideal thing to have as a defult cursor image.
       //guiContext->getMouseCursor().setDefaultImage("TaharezLook/MouseArrow");

       // load font and setup default if not loaded via scheme
       //Font& defaultFont = FontManager::getSingleton().createFromFile("DejaVuSans-12.font");
       // Set default font for the gui context
       //guiContext->setDefaultFont(&defaultFont);

       // A FrameWindow is a window with a frame and a titlebar which may be moved around
       // and resized.
       //
       // Create a FrameWindow in the TaharezLook style, and name it 'Sample Window'
       //FrameWindow* wnd = (FrameWindow*)winMgr->createWindow("TaharezLook/FrameWindow", "Sample Window");

       // Here we attach the newly created FrameWindow to the previously created
       // DefaultWindow which we will be using as the root of the displayed gui.
       mRoot->addChild(wnd);

       // Windows are in Relative metrics mode by default.  This means that we can
       // specify sizes and positions without having to know the exact pixel size
       // of the elements in advance.  The relative metrics mode co-ordinates are
       // relative to the parent of the window where the co-ordinates are being set.
       // This means that if 0.5f is specified as the width for a window, that window
       // will be half as its parent window.
       //
       // Here we set the FrameWindow so that it is half the size of the display,
       // and centered within the display.
       wnd->setPosition(UVector2(cegui_reldim(0.05f), cegui_reldim(0.05f)));
       wnd->setSize(USize(cegui_reldim(0.9f), cegui_reldim(0.9f)));

       // now we set the maximum and minum sizes for the new window.  These are
       // specified using relative co-ordinates, but the important thing to note
       // is that these settings are aways relative to the display rather than the
       // parent window.
       //
       // here we set a maximum size for the FrameWindow which is equal to the size
       // of the display, and a minimum size of one tenth of the display.
       wnd->setMaxSize(USize(cegui_reldim(1.0f), cegui_reldim(1.0f)));
       wnd->setMinSize(USize(cegui_reldim(0.01f), cegui_reldim(0.01f)));

       // As a final step in the initialisation of our sample window, we set the window's
       // text to "Hello World!", so that this text will appear as the caption in the
       // FrameWindow's titlebar.
       wnd->setText("K_EngineUI works!");

       wnd->subscribeEvent(CEGUI::Window::EventMouseClick, Event::Subscriber(&UIManager::handleHelloWorldClicked, this));
    }

    UiElement UIManager::addText(std::string text_, std::pair<float, float> pos)
    {
        //Creation of the element
        UiElement t;

        //Converting the position to topLeft corner because CEGUI isnt coherent with its own self
        pos.first -= 0.48;
        pos.second -= 0.48;

        //It is text
        t.type = Text;

        //Creation from the scheme
        t.wnd = winMgr->createWindow("TaharezLook/Label");

        //Adding as a child so we see it
        mRoot->addChild(t.wnd);

        //Its msg
        t.wnd->setText(text_);

        //Position
        t.wnd->setPosition(UVector2(cegui_reldim(pos.first), cegui_reldim(pos.second)));

        //You cannot change the size of a text in CEGUI for some reason
        t.wnd->setSize(USize(cegui_reldim(1), cegui_reldim(1)));

        //Return of the element
        return t;
    }

    ProgressBar* UIManager::addProgressBar(std::pair<float, float> pos, std::pair<float, float> size)
    {
        //Creation of the element
        ProgressBar* bar;

        //Creation from the scheme
        bar = (ProgressBar*)winMgr->createWindow("TaharezLook/ProgressBar");

        //Adding as a child so we see it
        mRoot->addChild(bar);

        //Position
        bar->setPosition(UVector2(cegui_reldim(pos.first), cegui_reldim(pos.second)));

        //You cannot change the size of a text in CEGUI for some reason
        bar->setSize(USize(cegui_reldim(size.first), cegui_reldim(size.second)));

        //Return of the element
        return bar;
    }

    /*************************************************************************
        Cleans up resources allocated in the initialiseSample call.
    *************************************************************************/
    bool UIManager::Shutdown()
    {
        try {
            instance.get()->closeContext();

            instance.reset(nullptr);

        }
        catch (const std::exception&) {
            return false;
        }

        return true;
    }

    void UIManager::closeContext()
    {
        winMgr->destroyAllWindows();
        CEGUI::System::getSingleton().destroyGUIContext(*guiContext);
        m_renderer->destroySystem();
    }
}