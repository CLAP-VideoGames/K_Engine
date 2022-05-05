#include "Animator.h"

#include <OgreCamera.h>
#include <OgreNode.h>
#include <OgreAnimationState.h>
#include <OgreEntity.h>

#include <ecs_prj/Entity.h>

#include <components_prj/Transform.h>
#include <components_prj/MeshRenderer.h>

#include <utils_prj/Timer.h>
#include <utils_prj/checkML.h>
#include <utils_prj/K_Map.h>

namespace K_Engine {
	//Required
	std::string Animator::name = "Animator";

	std::string Animator::GetId() {
		return name;
	}

	Animator::Animator(): Component() {
		defaultAnim = "None";
		startsEnabled = false;
	}

	Animator::Animator(Entity* e) : Component(e) {
		defaultAnim = "None";
		startsEnabled = false;
	}

	Animator::~Animator() {
		delete currentState_;
	}

	void Animator::init(K_Map* information) {
		defaultAnim = information->value("defaultAnim");
		startsEnabled = information->valueToBool("startsEnabled");
	}

	void Animator::awake()
	{
		// Obtenemos los componentes y entidades necesarios
		tr_ = entity->getComponent<Transform>();
		mesh_ = entity->getComponent<MeshRenderer>();

		node_ = mesh_->getOgreNode();
		ogreEntity_ = mesh_->getOgreEntity();
		mesh_->debug(); // print all anims

		// Recogemos todos los estados que traiga la malla
		animStatesMap_ = ogreEntity_->getAllAnimationStates();

		currentState_ = new AnimStateInfo();

		stopAllAnims = false;

		if (defaultAnim != "None")
			playAnim(defaultAnim);
	}

	void Animator::update(int frameTime)
	{
		// Actualizamos la animacion actual
		if(currentState_->animation != nullptr && !stopAllAnims)
			currentState_->animation->addTime(Ogre::Real(frameTime/1000.0f));
	}

	void Animator::setAnimTransition(std::string src, std::string dest, bool cond)
	{
		AnimTransition next ({ dest, cond });
	}

	void Animator::setAnimBool(std::string anim, std::string condName, bool value)
	{
		animTransitionsMap_.at(anim).at(condName)->cond = value;
	}

	void Animator::setEnable(bool state)
	{
		currentState_->animation->setEnabled(state);
	}

	void Animator::setLoop(bool state)
	{
		currentState_->animation->setLoop(state);
	}

	bool Animator::getAnimBool(std::string anim, std::string condName)
	{
		return animTransitionsMap_.at(anim).at(condName)->cond;
	}
	
	std::string Animator::getCurrAnimName()
	{
		return currentState_->name;
	}

	bool Animator::getEnable()
	{
		return currentState_->animation->getEnabled();
	}

	bool Animator::getLoop()
	{
		return currentState_->animation->getLoop();
	}

	bool Animator::animHasEnded()
	{
		return currentState_->animation->hasEnded();
	}

	void Animator::playAnim(std::string anim, bool loop)
	{
		if(currentState_->animation != nullptr)
			currentState_->animation->setEnabled(false);

		try
		{
			currentState_->name = anim;
			currentState_->animation = animStatesMap_->getAnimationState(anim);
			currentState_->animation->setEnabled(true);
			currentState_->animation->setLoop(loop);
			currentState_->animation->setTimePosition(0);
		}
		catch (const std::exception&){
		}
		
	}

	void Animator::stopAnim()
	{
		stopAllAnims = true;
	}

	void Animator::resumeAnim()
	{
		stopAllAnims = false;
	}

	void Animator::manageAnimTransitions()
	{
		// ANYSTATE
		for (auto t : animTransitionsMap_.at("anyState"))
		{
			// Si alguna de las transiciones desde el anyState estan a true cambiamos el estado
			if (t.second->cond)
			{
				currentState_->name = t.second->nextState;
				currentState_->animation = animStatesMap_->getAnimationState(t.second->nextState);
				currentState_->animation->setWeight(0);
				currentState_->animation->setTimePosition(0);
				return; // cortamos el metodo
			}
		}

		// CURRENTSTATE
		for (auto t : animTransitionsMap_.at(currentState_->name))
		{
			// Si alguna de las transiciones desde el currentState estan a true cambiamos el estado
			if (t.second->cond)
			{
				currentState_->name = t.second->nextState;
				currentState_->animation = animStatesMap_->getAnimationState(t.second->nextState);
				currentState_->animation->setWeight(0);
				currentState_->animation->setTimePosition(0);
				return; // cortamos el metodo
			}
		}
	}
}
