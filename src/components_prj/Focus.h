#pragma once
#ifndef FOCUS_H
#define FOCUS_H

#include <ecs_prj/Component.h>

namespace K_Engine {
	class UIManager;
	class UIImage;
	class Transform;
	class InputManager;
	class UIManager;
	class UIElement;
	class Timer;

	/// <summary>
	/// This class provides an entity with a UiImage component
	/// </summary>
	class __declspec(dllexport) Focus : public Component
	{
	public:
		Focus();

		/// <summary>
		/// Required to be initialized properly in the Component Manager
		/// </summary>
		/// <param name="e">Entity to be attached to</param>
		Focus(Entity* e);

		/// <summary>
		/// Creates a focus with the specified name. The image material must be previously loaded.
		/// </summary>
		/// <param name="overlayName">Name of the element</param>
		/// <param name="imageName">Name of the image material</param>
		Focus(Entity* e, std::string overlayName, std::string name);

		virtual ~Focus();

		// required method for the component name
		static std::string GetId();

		virtual void init(K_Map* information);

		virtual void onDisable();

		// It's called at the beginning of the execution.
		virtual void start();

		// It's called every frame of the game.
		virtual void update(int frameTime);

	private:
		//Required
		static std::string name;

		Transform* transformRf_; // Reference to transform Component
		UIImage* image_;         // Image created in UIManager

		// Basic attributes needed for the image
		std::string overlayName_;
		std::string imageName_;

		InputManager* inputMan;
		UIManager* uiManager;

		UIElement* currentElement;
		UIElement* elementToMoveTo_;

		Timer* timerToUpdate;

		int imageOffset;

		void syncData();
		void processMovement();
	};
}
#endif FOCUS_H