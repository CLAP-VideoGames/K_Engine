#pragma once
#ifndef SLIDER_H
#define SLIDER_H

#include <ecs_prj/Component.h>

namespace K_Engine {
	class UIManager;
	class UISlider;
	class Transform;
	class InputManager;
	struct Rectangle;
	class UIProgressBar;
	/// <summary>
	/// This class provides an entity with a UiScrollBar component
	/// </summary>
	class __declspec(dllexport) Slider : public Component
	{
	public:
		Slider();

		/// <summary>
		/// Required to be initialized properly in the Component Manager
		/// </summary>
		/// <param name="e">Entity to be attached to</param>
		Slider(Entity* e);

		/// <summary>
		/// Creates a scroll bar with the specified name. The image material must be previously loaded.
		/// </summary>
		/// <param name="e">Entity to be attached</param>
		/// <param name="overlayName">Name of the element</param>
		/// <param name="imageName">Name of the image material</param>
		Slider(Entity* e, std::string overlayName, std::string imageName, int y, int leftLimit, int rightLimit);
		virtual ~Slider();

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

	private:
		//Required
		static std::string name;

		//Reference to transform Component
		Transform* transformRf_ = nullptr;

		//ScrollBar created in UIManager
		UISlider* slider_;

		//Basic attributes needed for the image
		std::string overlayName_;
		std::string imageName_;
		int y_;
		int leftLimit_;
		int rightLimit_;

		InputManager* inputMan;

		Rectangle* inputArea;

		bool pressed_;

		UIProgressBar* progressBar_;
	};
}


#endif SLIDER_H