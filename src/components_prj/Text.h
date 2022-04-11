#pragma once
#ifndef TEXT_H
#define TEXT_H

#include <ecs_prj/Component.h>

namespace K_Engine {
	class UIManager;
	class UiText;
	class Transform;
	/// <summary>
	/// This class provides an entity with a UiImage component
	/// </summary>
	class __declspec(dllexport) Text : public Component
	{
	public:
		/// <summary>
		/// Required to be initialized properly in the Component Manager
		/// </summary>
		/// <param name="e">Entity to be attached to</param>
		Text(Entity* e);

		/// <summary>
		/// Creates text with the specified name.
		/// </summary>
		/// <param name="e">Entity to be attached</param>
		/// <param name="overlayName">Name of the element</param>
		/// <param name="text">Text to display</param>
		Text(Entity* e, std::string overlayName, std::string text);
		~Text();

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

		//Text created in UIManager
		UiText* uitext_;

		//Basic attributes needed for the text
		std::string overlayName_;
		std::string text_;
	};
}


#endif TEXT_H