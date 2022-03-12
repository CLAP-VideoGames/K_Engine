#pragma once
#ifndef COMPONENT_H
#define COMPONENT_H

#include <string>;

//class Entity;
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

#pragma region VirtualMethods
	//update is called every frame of the game
	virtual void update(){};

	//start is called once the game starts
	virtual void start(){};

	//awake is called every time the component is activated
	virtual void awake(){};

	//onEnable is called every time the component is enabled
	virtual void onEnable() {};

	//onDisable is called every time the component is disabled
	virtual void onDisable() {};

	//physicsUpdate is called before update and it calls everyPhysic we need
	virtual void physicsUpdate() {}

	//Temporary method to develop our components
	//(LLamad aqui a lo que querais testear de cada componente)
	//This method is called in Entity add component, so it executes everyTime
	//You add a component to an entity
	virtual void debug() {};
#pragma endregion

	//Active/Deactivate our component 
	void setActive(bool a);

protected:
	//Default string to force the user to give it a diferent id 
	std::string id;
	Entity* entity;

	bool enable;

	Component(std::string id, Entity* ent);
};
#endif	