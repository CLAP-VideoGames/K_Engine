#pragma once
#ifndef COMPONENTMANAGER_H
#define COMPONENTMANAGER_H

#include <memory>
#include <stdexcept>
#include <unordered_map>


namespace K_Engine {
	//Podemos usar esta clase para administrar que el usuario no pueda añadir componentes
	//Sin las cosas que queremos que añada

		/*
		* Declaration of the Component class so we do not have
		* to include it in our file
		*/
	class Component;
	class Entity;

	/*
	* Component Manager is the class responsible of the administration
	* of external and base component for our games, we add external components
	* to the engine using the Add method.
	*/
	class __declspec(dllexport) ComponentManager {
	public:
		//Default Constructor to avoid problems in the future
		ComponentManager();
		~ComponentManager();

		//static method to get the manager instance in every file we want
		static ComponentManager* GetInstance();

		//in init we Initialize the base components of our engine
		//Declare here your components when you end programming them
		//Use Transform as an example
		static bool Init();
		static bool Shutdown();

		//This method allows the user to add its own components to the engine
		//This method makes sure that the GetId() method is declared
		template <typename T>
		void add() {
			//throw std::invalid_argument("Your component does not contain a GetId() method, declare it and try again");
			//The user is not allowed to add a component without an static GetId() method
			if (!existingComponent(T::GetId())) 
				availableComponents.emplace(T::GetId(), &ComponentManager::createComponent<T>);
		}

		//We can catch an exception here if we want (LOOK AT IT AGAIN)
		template<typename T, typename ...Ts>
		T* create(Entity* e, Ts &&... args) {
			//We check if the component exists
			if (!existingComponent(T::GetId()))
				throw std::invalid_argument("There is no component with that name");

			//We return a new instance of our component
			auto newComponent = new T(e, args...);

			return newComponent;
		}

		//template<typename T>
		Component* createByName(std::string name);

		std::vector<std::string> getAvailableComponents();

	private:
		//unique pointer for our instance so we do not have problems of sharing the memory 
		static std::unique_ptr<ComponentManager> instance;

		//Map to store the current components 
		std::unordered_map<std::string, Component* (*)()> availableComponents;

		//Not sure if this is going to be useful, but its simple code
		bool existingComponent(std::string compName);

		template<typename T>
		static Component* createComponent() {
			return new T();
		}
	};
}
#endif // COMPONENTMANAGER_H