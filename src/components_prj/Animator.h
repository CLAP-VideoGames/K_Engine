#pragma once
#ifndef ANIMATOR_H
#define ANIMATOR_H

#include <ecs_prj/Component.h>
#include <map>

namespace K_Engine {

	namespace Ogre {
		class AnimationState;
		class AnimationStateSet;
		class SceneNode;
		class Entity;
	}

	class MeshRenderer;
	class Transform;

	struct AnimTransition {
		std::string nextState;
		bool cond;
	};

	struct AnimStateInfo {
		Ogre::AnimationState* animation;
		std::string name;
	};


	class __declspec(dllexport) Animator : public Component
	{
	public:
		/// <summary>
		/// Required to be initialized properly in the Component Manager
		/// </summary>
		/// <param name="e">Entity to be attached to</param>
		Animator(Entity* e);

		~Animator();

		//Required method for the component name
		static std::string GetId();

		/// <summary>
		/// It's called at the beginning of the execution.
		/// </summary>
		virtual void start();

		/// <summary>
		/// It's called every frame of the game.
		/// </summary> 
		virtual void update();

		/// <summary>
		/// Custom method for debugging.
		/// </summary>
		virtual void debug() {};

		//Setters
		void setAnimBool(std::string anim, std::string condName, bool value);

		//Getters
		bool getAnimBool(std::string anim, std::string condName);

	private:

		//Punteros a nodos y entidad de Ogre y componentes Transform y Mesh
		Ogre::SceneNode* node_;
		Ogre::Entity* ogreEntity_;
		Transform* tr_ = nullptr;
		MeshRenderer* mesh_ = nullptr;


		//Mapa de Ogre con las animaciones de la malla
		Ogre::AnimationStateSet* animStatesMap_;

		//Estado Actual
		AnimStateInfo* currentState_;

		//Mapa con todas las animaciones y sus correspondientes transiciones
		//nombre de la animacion	//Transiciones
		std::map<std::string, std::map<std::string, AnimTransition*>> animTransitionsMap_;

		//Required
		static std::string name;

		//Gestión cambio de estados
		void manageAnimTransitions();
	};
}
#endif ANIMATOR_H