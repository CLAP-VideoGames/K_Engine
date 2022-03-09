#pragma once
#ifndef UIMANAGER_H
#define UIMANAGER_H

#include <memory>

namespace CEGUI
{
    class Window;
    class DefaultWindow;
    class EventArgs;
    class GUIContext;
}

class UIManager
{
public:
    UIManager();
    ~UIManager();

    static UIManager* getInstance();

    void init();
    void shutdown();

private:
    static std::unique_ptr<UIManager> instance;

    CEGUI::DefaultWindow* mRoot;
    CEGUI::GUIContext* guiContext;


    //Getters
    bool handleHelloWorldClicked(const CEGUI::EventArgs& args);

};
#endif // UIMANAGER_H
