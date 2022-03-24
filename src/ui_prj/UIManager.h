#pragma once
#ifndef UIMANAGER_H
#define UIMANAGER_H
//This constant is used to make every UIElement have the same logic
//We have to do this because CEGUI decided that position(0,0) for a text
//Is the center of the screen and position(0,0) for a progress bar is topLeft
#define CEGUIOFSETT = 0.48;

#include <memory>
#include <string>
#include <vector>

namespace CEGUI {
	class Window;
	class DefaultWindow;
	class EventArgs;
	class GUIContext;
	class WindowManager;
	class OgreRenderer;
	class FrameWindow;
	class ProgressBar;
	class ButtonBase;
}

//UIComponents
class UIComponent;
class UISlider;
class UIScrollbar;


enum UITypes {Button, Slider, ScrollBar, MarkBox, Pointer, Image, Text};

/// <summary>
/// type = Button/Label/whatever you need to put in the scheme
/// Text = "" if it has no text or "whatever" if it has text
/// wnd = the window CEGUI return from its creation, so we accest it
/// </summary>
/// 
/// ����IMPORTANT FOR DEVELOPERS!!!! MAYBE U HAVE TO USE ANOTHER CLASS LIKE PROGRESSBAR
/// IF IT HAS ITS OWN METHODS LIKE PROGRESS BAR, DONT USE THIS STRUCT AND ERASE
/// THE TYPE FROM THE ENUM ABOVE, IF THE USER IS ONLY GOING TO NEED THE METHODS
/// FORM WINDOW, USE THIS STRUCT AND CREATE A METHOD LIKE ADDTEXT
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
		/// <param name="pos">Position(0,0) is top left o the screen </param>
		/// <param name="size"> You cannot change size because CeGuI also it seems u cannot change font size </param>
		/// <returns></returns>
		UiElement addText(std::string text_,
			std::pair<float,float> pos = std::pair<float,float>(0,0));

		/// <summary>
		/// This method adds a progress bar in the given position and with the given scale
		/// (0,0) is top left of the screen
		/// We can not return UiElement here because we dont want the user to cast the elemnt every time
		/// </summary>
		/// <returns></returns>
		CEGUI::ProgressBar* addProgressBar(std::pair<float, float> pos = std::pair<float, float>(0, 0),
			std::pair<float, float> size = std::pair<float, float>(0, 0));

		/// <summary>
		/// This method adds a slider in the given position and with the given scale
		/// (0,0) is top left of the screen
		/// </summary>
		/// <returns></returns>
		UISlider* createSlider(std::pair<float, float> pos, std::pair<float, float> size = std::pair<float, float>(1, 1), std::string name = "UISlider", float value = 0);
		/// <summary>
		/// This method adds a button in the given position and scale. (0, 0) is the upper-left corner.
		/// </summary>
		/// <returns></returns>
		CEGUI::ButtonBase* addButton(std::string text, std::pair<float, float> pos = std::pair<float, float>(0, 0),
			std::pair<float, float> size = std::pair<float, float>(0, 0));

		/// <summary>
		/// This method adds a slider in the given position and with the given scale
		/// (0,0) is top left of the screen
		/// </summary>
		/// <returns></returns>
		UIScrollbar* createScrollbar(std::pair<float, float> pos, std::pair<float, float> size = std::pair<float, float>(1, 1), std::string name = "UIScrollbar", float value = 0);

	private:
		static std::unique_ptr<UIManager> instance;
		std::string name;
		std::string schemeName;

		CEGUI::GUIContext* guiContext;
		CEGUI::DefaultWindow* mRoot;
		CEGUI::WindowManager* winMgr;
		CEGUI::OgreRenderer* m_renderer;
		CEGUI::FrameWindow* wnd;

		std::vector<UIComponent*> ceguiElements;

		void initContext();
		void initRoot();
		void initScheme();

		void cleanElements();
		void closeContext();
	};
}
#endif // UIMANAGER_H