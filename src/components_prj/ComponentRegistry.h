#pragma once
#ifndef COMPONENTREGISTRY_H
#define COMPONENTREGISTRY_H

#include <components_prj/Transform.h>
#include <components_prj/RigidBody.h>
#include <components_prj/MeshRenderer.h>
#include <components_prj/AudioSource.h>
#include <components_prj/Light.h>

#include <ecs_prj/ComponentManager.h>

namespace K_Engine {
	namespace Registry {
		inline void registerComponents() {
			ComponentManager* compMan = K_Engine::ComponentManager::GetInstance();

			compMan->add<K_Engine::Transform>();
			compMan->add<K_Engine::MeshRenderer>();
			compMan->add<K_Engine::RigidBody>();
			compMan->add<K_Engine::AudioSource>();
			compMan->add<K_Engine::Light>();
		}
	}
}
#endif // GAMECOMPONENTREGISTRY_H