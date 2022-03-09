#pragma once
#ifndef UIMANAGER_H
#define UIMANAGER_H

#include <memory>
#include <string>

namespace CEGUI
{
    class Window;
    class DefaultWindow;
    class EventArgs;
    class GUIContext;
    class WindowManager;
    class OgreRenderer;
    class FrameWindow;
    class Scheme;
}

class UIManager
{
public:
    UIManager();
    ~UIManager();

    static UIManager* GetInstance();

    static bool Init(std::string n);
    static bool Shutdown();

private:
    static std::unique_ptr<UIManager> instance;
    std::string name;

    CEGUI::GUIContext* guiContext;
    CEGUI::DefaultWindow* mRoot;
    CEGUI::WindowManager* winMgr;
    CEGUI::OgreRenderer* m_renderer;
    CEGUI::FrameWindow* wnd;
    CEGUI::Scheme* sch;

    void initContext();
    void initRoot();
    void initResources();

    bool handleHelloWorldClicked(const CEGUI::EventArgs& args);

    void closeContext();
};
#endif // UIMANAGER_H
