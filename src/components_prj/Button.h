#pragma once
#ifndef BUTTON_H
#define BUTTON_H

#include <ecs_prj/Component.h>

#include <functional>

namespace K_Engine {
	class UIManager;
	class UiButton;
	class Transform;
	/// <summary>
	/// This class provides an entity with a UIButton component
	/// </summary>
	class __declspec(dllexport) Button : public Component
	{
	public:
		/// <summary>
		/// Required to be initialized properly in the Component Manager
		/// </summary>
		/// <param name="e">Entity to be attached to</param>
		Button(Entity* e);

		/// <summary>
		/// Creates a button with the specified name and images to be used in it's different states. This images must be previously loaded.
		/// </summary>
		/// <param name="e">Entity to be attached</param>
		/// <param name="overlayName">Name of the element</param>
		/// <param name="imageName">Name of the default image material</param>
		/// <param name="hoverImageName">Name of the image to be displayed when the button is hovered</param>
		/// <param name="pressedImageName">Name of the image to be displayed when the button is pressed</param>
		Button(Entity* e, std::string overlayName, std::string imageName, std::string hoverImageName, std::string pressedImageName);
		~Button();

		//Required method for the component name
		static std::string GetId();

		/// <summary>
		/// It's called at the beginning of the execution.
		/// </summary>
		virtual void start();

		/// <summary>
		/// It's called every frame of the game.
		/// </summary> 
		virtual void update(int frameTime);

		/// <summary>
		/// Sets a function to be called when button is pressed
		/// </summary>
		/// <param name="Function">Function to be called, declaration example: void Function();</param>
		void setButtonClick(std::function<void(void*)> function);

	private:
		//Required
		static std::string name;

		//Reference to transform Component
		Transform* transformRf_ = nullptr;

		//Button created in UIManager
		UiButton* button_;

		//Basic attributes needed for the button
		std::string overlayName_;
		std::string imageName_;

		//Extra attributes for button
		std::string hoverImageName_;
		std::string pressedImageName_;

		//Function callback
		std::function<void(void*)> onButtonClick = nullptr;
	};
}


#endif BUTTON_H