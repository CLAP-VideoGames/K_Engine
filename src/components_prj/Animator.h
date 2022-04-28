#pragma once
#ifndef ANIMATOR_H
#define ANIMATOR_H

#include <map>

#include <ecs_prj/Component.h>

namespace Ogre {
	class AnimationState;
	class AnimationStateSet;
	class SceneNode;
	class Entity;
}

namespace K_Engine {

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

		Animator();

		/// <summary>
		/// Required to be initialized properly in the Component Manager
		/// </summary>
		/// <param name="e">Entity to be attached to</param>
		Animator(Entity* e);

		virtual ~Animator();

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

		/// <summary>
		/// Custom method for debugging.
		/// </summary>
		virtual void debug() {};

		//Setters
		void setAnimBool(std::string anim, std::string condName, bool value);
		void setEnable(bool state);
		void setLoop(bool state);

		//Getters
		bool getAnimBool(std::string anim, std::string condName);
		std::string getCurrAnimName();
		bool getEnable();
		bool getLoop();
		bool animHasEnded();

		//Features
		void playAnim(std::string anim);
		void stopAnim();
		void resumeAnim();

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

		//Flags
		bool stopAllAnims;
	};
}
#endif ANIMATOR_H