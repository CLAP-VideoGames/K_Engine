#include "Scene.h"

#include <ecs_prj/EntityManager.h>
#include <ecs_prj/Entity.h>
#include <script_prj/ScriptManager.h>
#include <sound_prj/AudioManager.h>

// SOON TO BE DELETED
#include <physics_prj/PhysicsManager.h>
#include <physics_prj/CollisionLayers.h>

#include <render_prj/RenderManager.h>
#include <render_prj/Camera.h>

#include <components_prj/Transform.h>
#include <components_prj/Animator.h>
#include <components_prj/MeshRenderer.h>
#include <components_prj/RigidBody.h>
#include <components_prj/AudioSource.h>
#include <components_prj/Light.h>
#include <components_prj/Button.h>
#include <components_prj/Image.h>
#include <components_prj/ProgressBar.h>
#include <components_prj/Text.h>
#include <components_prj/Slider.h>

#include <utils_prj/Vector3.h>
#include <utils_prj/checkML.h>

namespace K_Engine {
	Scene::Scene() {
		entMan = new EntityManager();
		scriptMan = K_Engine::ScriptManager::GetInstance();
	}

	Scene::Scene(std::string sceneName) : Scene() {
		name = sceneName;
	}

	Scene::~Scene() {
		entMan->hideElements();
		delete entMan;
	}

	void Scene::init(std::string nameMap) {
		loadScene(nameMap);

		//Awake of the entities
		entMan->awake();
		//First onEnable
		entMan->onEnable();
		//Start of the entites
		entMan->start();
	}

	void Scene::init() {
		loadScene(name);

		entMan->awake();
		entMan->onEnable();
		entMan->start();
	}

	void Scene::update(int frameTime) {
		entMan->update(frameTime);
	};

	void Scene::fixedUpdate(int deltaTime) {
		entMan->fixedUpdate(deltaTime);
	}

	void Scene::hideElements() {
		entMan->hideElements();
	}

	void Scene::showElements() {
		entMan->showElements();
	}

	std::string Scene::getName() {
		return name;
	}

	bool Scene::loadScene(std::string nameMap) {
		scriptMan->loadLuaScene(nameMap, entMan);
		return true;
	}
}