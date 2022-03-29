#pragma once
#ifndef COMPONENT_H
#define COMPONENT_H

#include <string>;

namespace K_Engine {
	class Entity;

	/// <summary>
	/// You have to specify the id of the component with a string
	/// The engine will throw an exception otherwise
	/// 
	/// You have to specify your getId() Method
	/// 
	/// Use Transform.h and Tranform.cpp as examples
	/// 
	/// Example:
	/// class MyComponent : public Component{
	/// public(necesary):
	///		static std::string getId() { return myVariable; } (This method MUST be named this way)
	/// 
	///  *All your virtual methods like update or awake*
	/// 
	///  private(preferibly private):
	///		static std::string myVariable; (You can name it whatever you want but name is pretty descriptive)
	/// }
	/// </summary>
	class Component
	{
	public:
		~Component();

		//awake is called every time the component is activated
		virtual void awake();

		//start is called once the game starts
		virtual void start();

		//onEnable is called every time the component is enabled
		virtual void onEnable();

		//update is called every frame of the game
		virtual void update();

		//physicsUpdate is called before update and it calls everyPhysic we need
		virtual void physicsUpdate();

		//onDisable is called every time the component is disabled
		virtual void onDisable();

		//Temporary method to develop our components
		//This method is called in Entity add component, so it executes everyTime
		//You add a component to an entity
		virtual void debug();

		virtual void onCollisionEnter(Entity* collision) {};

		virtual void onCollisionStay(Entity* collision) {};

		virtual void onCollisionExit(Entity* collision) {};

		//Active/Deactivate our component 
		void setActive(bool a);

	protected:
		//Default string to force the user to give it a diferent id 
		std::string id;
		bool enable;

		Entity* entity;

		Component(std::string id, Entity* ent);
	};
}
#endif	// COMPONENT_H