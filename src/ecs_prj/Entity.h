#pragma once
#ifndef ENTITY_H
#define ENTITY_H

#include <unordered_map>
#include <stdexcept>

#include <ecs_prj/ComponentManager.h>

namespace K_Engine {
	class Component;
	class EntityManager;

	/*
	*Our class Entity starts with only a Transform Component, which contains the rotation, position and scale of our entity
	*You can alterate you entitys with the following methods
	*/
	class __declspec(dllexport) Entity {
	public:
		Entity();
		~Entity();

		//Template to get a Component
		template<typename T>
		T* getComponent() {
			std::string compName = getComponentName<T>();

			auto iterator = components.find(compName);

			if (iterator != components.end()) return static_cast<T*>(components[compName]);

			return nullptr;
		};

		//Template to remove a Component
		template<typename T>
		void removeComponent() {
			std::string compName = getComponentName<T>();

			auto iterator = components.find(compName);

			//If the entity has the component we remove it
			if (hasComponent<T>()) {
				auto it = components.find(compName);

				components.erase(it);

				delete components[compName];

				components[compName] = nullptr;
			}
		}

		//Templete to check if an Entity has an specific component
		template <typename T>
		bool hasComponent() {
			std::string compName = getComponentName<T>();

			auto iterator = components.find(compName);

			return (iterator != components.end());
		}

		//Template to add any Component to our Entity
		template <typename T, typename ...Ts>
		T* addComponent(Ts &&... args) {
			std::string compName = getComponentName<T>();

			ComponentManager* comM = ComponentManager::GetInstance();

			T* c = comM->create<T>(this, args...);

			components.emplace(compName, c);

			return static_cast<T*>(c);
		}

		//Template to add any Component to our Entity
		Component* addComponentByName(std::string name);

		//This mehtos is used to set our Entity to active or unactive
		void setActive(bool a);

		/// <summary>
		/// This method updates our entity and is called once per frame, requires time between frames
		/// </summary>
		/// <param name="collision"></param>
		void update(int frameTime);

		/// <summary>
		/// This method updates components with physics, requires fixed deltaTime
		/// </summary>
		/// <param name="collision"></param>
		void fixedUpdate(int deltaTime);

		//To know when to destroy our entity
		bool destroyed() { return toDestroy; }

		//To know when to update our entity
		bool isActive() { return active; }

		//Awake of everyComponent
		void awake();

		//Enable of everyComponent
		void onEnable();

		//The start of everyComponent of our entity
		void start();

		//Destroy this object and all its components
		void destroy();

		//Add an entity to the children vector
		void addChild(Entity* child);

		//Getter for the children vector
		std::vector<Entity*> getChildren() { return children; }

		EntityManager* getMan() { return entMan; }

		void setMan(EntityManager* e) { entMan = e; }
	private:

		/*
		*We use this method to check that it is a Component what the user is introucing in our methods,
		*if it is not we throw an exception, if it is we return the componentName
		*/
		template<typename T>
		std::string getComponentName() {
			std::string compName;
			try {
				compName = T::GetId();
			}
			catch (std::string msg) {
				throw std::invalid_argument("There is no component with that name");
			}

			return compName;
		}

		bool active;    // determines if we update the entity or not
		bool toDestroy; // knows when do we have to erase an entity

		//Map to find our components and erase them using the id of the component
		std::unordered_map<std::string, Component*> components;

		//strings to give the entity a tag or a name
		std::string tag;
		std::string name;

		//Entitys attached to thi entity
		std::vector<Entity*> children;

		//The entity manager of the entity´s scene
		EntityManager* entMan;
	};
}
#endif // ENTITY_H