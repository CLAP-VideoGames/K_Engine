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

enum UITypes {Button, Slider, ScrollBar, MarkBox, Pointer, Image, Text};

/// <summary>
/// type = Button/Label/whatever you need to put in the scheme
/// Text = "" if it has no text or "whatever" if it has text
/// wnd = the window CEGUI return from its creation, so we accest it
/// </summary>
struct UiElement {

	UITypes type;
	CEGUI::Window* wnd;
	
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

		/// <summary>
		/// Adds a text in the x = 0 and y = 0, with 1 as defauult size
		/// Then we return an UiElement so the user can handle it as it wishes
		/// </summary>
		/// <param name="text_"> what you text will show </param>
		/// <param name="pos"> the position u want your text.(0,0) is the center
		/// of the screen, using values in the interval [0, 0.5) should be engough
		/// to set the position u want </param>
		/// <param name="size"> the size you want your text to be </param>
		/// <returns></returns>
		UiElement addText(std::string text_,
			std::pair<float,float> pos = std::pair<float,float>(0,0),
			std::pair<float, float> size = std::pair<float, float>(1, 1));

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