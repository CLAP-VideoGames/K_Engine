#pragma once
#ifndef TEXT_H
#define TEXT_H

#include <ecs_prj/Component.h>

namespace K_Engine {
	class UIManager;
	class UIText;
	class Transform;
	class Vector3;

	/// <summary>
	/// This class provides an entity with a UiImage component
	/// </summary>
	class __declspec(dllexport) Text : public Component
	{
	public:
		Text();

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

		virtual ~Text();

		//Required method for the component name
		static std::string GetId();

		virtual void init(K_Map* information);

		/// <summary>
		/// It's called at the beginning of the execution.
		/// </summary>
		virtual void start();

		/// <summary>
		/// It's called every frame of the game.
		/// </summary> 
		virtual void update(int frameTime);

		/// <summary>
		/// Sets the text value to a new string
		/// </summary>
		void changeText(std::string newText);

		void changeTextPosition(int x, int y);

	private:
		//Required
		static std::string name;

		//Reference to transform Component
		Transform* transformRf_ = nullptr;

		//Text created in UIManager
		UIText* uitext_;

		//Basic attributes needed for the text
		std::string overlayName_;
		std::string text_;

		int offsetY;
		int offsetX;
	};
}


#endif TEXT_H