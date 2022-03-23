#pragma once
#ifndef UIMANAGER_H
#define UIMANAGER_H

#include <memory>
#include <string>

namespace CEGUI {
	class Window;
	class DefaultWindow;
	class EventArgs;
	class GUIContext;
	class WindowManager;
	class OgreRenderer;
	class FrameWindow;
}

enum UITypes {Button, Slider, ScrollBar, MarkBox, Pointer, Image};

/// <summary>
/// type = Button/Label/whatever you need to put in the scheme
/// Text = "" if it has no text or "whatever" if it has text
/// wnd = the window CEGUI return from its creation, so we accest it
/// </summary>
struct UiElement {

	UITypes type;
	FrameWindow* wnd;
	
	// createButton(string mesg, std::Pair<float,float> size, std::Pair<float,float> pos){
	// UIELement newJIHAEW;
	//																	IMPORTANT SHIT					
	// FrameWindow* wnd = (FrameWindow*)winMgr->createWindow("TaharezLook/Button", "Sample Window");
	// 
	// UIElement.wnd = wnd;
	// type = Button;
	// 
	// return newJIHAEW;
	// }
	//wnd->setText(text);
	//return wnd;
};

namespace K_Engine {
	class UIManager {
	public:
		UIManager();
		~UIManager();

		static UIManager* GetInstance();

		static bool Init(std::string n);
		static bool Shutdown();

		void exampleUI();

	private:
		static std::unique_ptr<UIManager> instance;
		std::string name;

		CEGUI::GUIContext* guiContext;
		CEGUI::DefaultWindow* mRoot;
		CEGUI::WindowManager* winMgr;
		CEGUI::OgreRenderer* m_renderer;
		CEGUI::FrameWindow* wnd;


		void initContext();
		void initRoot();

		bool handleHelloWorldClicked(const CEGUI::EventArgs& args);

		void closeContext();
	};
}
#endif // UIMANAGER_H