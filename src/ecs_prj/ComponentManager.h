#pragma once
#ifndef COMPONENTFACTORY_H
#define COMPONENTFACTORY_H

#include <memory>
#include <unordered_map>

//Podemos usar esta clase para administrar que el usuario no pueda añadir componentes
//Sin las cosas que queremos que añada


/*
* Declaration of the Component class so we do not have 
* to include it in our file
*/
class Component;

/*
* Component Manager is the class responsible of the administration
* of external and base component for our games, we add external components
* to the engine using the Add method. 	
*/
class ComponentManager
{
public:
	//Default Constructor to avoid problems in the future
	ComponentManager();
	~ComponentManager() {};

	//static method to get the manager instance in every file we want
	static ComponentManager* GetInstance();

	//in init we Initialize the base components of our engine
	//Declare here your components when you end programming them
	//Use Transform as an example
	static bool Init();

	//We can catch an exception here if we want (LOOK AT IT AGAIN)
	template<typename T, typename ...Ts>
	T* create(Ts &&... args);

	//This method allows the user to add its own components to the engine
	//This method makes sure that the GetId() method is declared
	template <typename T>
	void add();

	//Not sure if this is going to be useful, but its simple code
	bool existingComponent(std::string compName);

private:
	//unique pointer for our instance so we do not have problems of sharing the memory 
	static std::unique_ptr<ComponentManager> instance;
	
	//Map to store the current components 
	std::unordered_map<std::string, Component*> availableComponents;
};

#endif
