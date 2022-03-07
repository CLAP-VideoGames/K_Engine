#ifndef COMPONENT_H
#define COMPONENT_H

#include <string>;
/// <summary>
/// You have to specify the id of the component with a string
/// The engine will throw an exception otherwise
/// 
/// You have to specify your getId() Method
/// 
/// Use Transform.h and Tranform.cpp as examples
/// </summary>
class Component
{
public:
	Component(std::string id);
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
#pragma endregion

	//Active/Deactivate our component 
	void setActive(bool a);

protected:
	//option 1: using an string to identify our components by name
	std::string id = "unknown";

	bool enable;
private:

};
#endif	