#pragma once
#ifndef COMPONENTREGISTRY_H
#define COMPONENTREGISTRY_H

#include <components_prj/Transform.h>
#include <components_prj/Animator.h>
#include <components_prj/RigidBody.h>
#include <components_prj/MeshRenderer.h>
#include <components_prj/AudioSource.h>
#include <components_prj/Light.h>
#include <components_prj/Button.h>
#include <components_prj/Image.h>
#include <components_prj/ProgressBar.h>
#include <components_prj/ScrollBar.h>
#include <components_prj/Text.h>
#include <components_prj/Slider.h>

#include <ecs_prj/ComponentManager.h>

namespace K_Engine {
	namespace Registry {
		inline void registerComponents() {
			ComponentManager* compMan = K_Engine::ComponentManager::GetInstance();

			compMan->add<K_Engine::Transform>();
			compMan->add<K_Engine::MeshRenderer>();
			compMan->add<K_Engine::RigidBody>();
			compMan->add<K_Engine::Animator>();
			compMan->add<K_Engine::AudioSource>();
			compMan->add<K_Engine::Light>();
			compMan->add<K_Engine::Button>();
			compMan->add<K_Engine::Image>();
			compMan->add<K_Engine::ProgressBar>();
			compMan->add<K_Engine::ScrollBar>();
			compMan->add<K_Engine::Text>();
			compMan->add<K_Engine::Slider>();
		}
	}
}
#endif // GAMECOMPONENTREGISTRY_H