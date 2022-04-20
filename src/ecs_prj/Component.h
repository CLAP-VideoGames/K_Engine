#pragma once
#ifndef COMPONENT_H
#define COMPONENT_H

#include <string>;

namespace K_Engine {
	class Entity;
	class K_Map;

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
	class __declspec(dllexport) Component {
	public:

		Component();

		Component(Entity* ent);

		virtual ~Component();

		/// <summary>
		/// awake is called every time the component is activated
		/// </summary>
		/// <param name="collision"></param>
		virtual void awake();

		/// <summary>
		/// start is called once the game starts
		/// </summary>
		/// <param name="collision"></param>
		virtual void start();

		/// <summary>
		/// Used to initialize via .Lua using scriptManager
		/// </summary>
		/// <param name="information"></param>
		virtual void init(K_Map* information) {};

		//onEnable is called every time the component is enabled
		virtual void onEnable();
		/// <summary>
		/// Update requires time between frames
		///update is called every frame of the game
		/// </summary>
		/// <param name="t"></param>
		virtual void update(int deltaTime);
		/// <summary>
		/// PhysicsUpdate is called before update and it calls everyPhysic we need
		/// PhysicsUpdate specific use for physics, requires fixed deltaTime
		/// </summary>
		/// <param name="deltaTime"></param>
		virtual void physicsUpdate(int deltaTime);

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
		bool enable;

		Entity* entity;
	};
}
#endif	// COMPONENT_H