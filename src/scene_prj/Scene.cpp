#include "Scene.h"

#include <ecs_prj/EntityManager.h>
#include <ecs_prj/Entity.h>

// SOON TO BE DELETED
#include <physics_prj/PhysicsManager.h>
#include <physics_prj/CollisionLayers.h>

#include <components_prj/Transform.h>
#include <components_prj/MeshRenderer.h>
#include <components_prj/RigidBody.h>
#include <components_prj/AudioSource.h>

namespace K_Engine {
	Scene::Scene()
	{
		entMan = new EntityManager();
	}

	Scene::~Scene()
	{
		delete entMan;
	}

	void Scene::init() {};

	void Scene::update() 
	{
		entMan->update();
	};

	void Scene::fixedUpdate()
	{
		entMan->fixedUpdate();
	}

	void Scene::debug()
	{
		entMan = new K_Engine::EntityManager(); // Entity Manager

		// example scene (pending of development)
		std::string playerLayer = "Player";
		std::string nothingLayer = "Nothing";
		std::string platformLayer = "Platform";

		int playerCollidesWith = K_Engine::PhysicsManager::GetInstance()->getLayerValue(platformLayer);
		//Configurations Scope
		K_Engine::Entity* player = entMan->addEntity();
		K_Engine::Transform* t = player->addComponent<K_Engine::Transform>(); t->setDimensions(3.0f);
		{
			t->setPosition(3, 6, 0);
			ColliderType boxType = ColliderType::CT_SPHERE;
			BodyType bodyType = BodyType::BT_DYNAMIC;
			float mass = 1.0f;
			RigidBody* r = player->addComponent<RigidBody>(boxType, bodyType, mass, K_Engine::PhysicsManager::GetInstance()->getLayerValue(playerLayer), playerCollidesWith);
			r->setFriction(0.6f);
			r->setRestitution(1.2f);
			K_Engine::MeshRenderer* m = player->addComponent<K_Engine::MeshRenderer>();
			m->setMesh("sphere.mesh");
			m->setMaterial("K_Engine/PrototypeBlue");
			m->debug();
		}

		K_Engine::Entity* playerChild = entMan->addEntity();
		{
			K_Engine::Transform* t = playerChild->addComponent<K_Engine::Transform>(); t->setDimensions(1.0f);
			t->setPosition(7, 7, 0);
			//t->setRotation(0, 0, 10);
			ColliderType boxType = ColliderType::CT_SPHERE;
			BodyType bodyType = BodyType::BT_DYNAMIC;
			float mass = 1.0f;
			//RigidBody* r = playerChild->addComponent<RigidBody>(boxType, bodyType, mass, physicsMan->getLayerValue(playerLayer), playerCollidesWith);
			//r->setFriction(0.6f);
			//r->setRestitution(1.2f);
			K_Engine::MeshRenderer* m = playerChild->addComponent<K_Engine::MeshRenderer>();
			m->setMesh("sphere.mesh");
			m->setMaterial("K_Engine/PrototypeBlue");
			m->debug();
		}
		player->addChild(playerChild);

		int platformCollidesWith = K_Engine::PhysicsManager::GetInstance()->getLayerValue(playerLayer);
		//Configurations Scope
		{
			K_Engine::Entity* platform = entMan->addEntity();
			K_Engine::Transform* t = platform->addComponent<K_Engine::Transform>(); t->setDimensions(5.f, 1.0f, 5.f);
			t->setPosition(-2.8, 0.f, 0);
			t->setRotation(0, 0, -45);
			ColliderType boxType = ColliderType::CT_BOX;
			BodyType bodyType = BodyType::BT_STATIC;
			K_Engine::RigidBody* r = platform->addComponent<K_Engine::RigidBody>(boxType, bodyType, 0.0f, K_Engine::PhysicsManager::GetInstance()->getLayerValue(platformLayer), platformCollidesWith);
			r->setRestitution(0.8f);
			K_Engine::MeshRenderer* m = platform->addComponent<K_Engine::MeshRenderer>();
			m->setMesh("cube.mesh");
			m->setMaterial("K_Engine/PrototypeOrange");
		}

		int futureCollidesWith = K_Engine::PhysicsManager::GetInstance()->getLayerValue(playerLayer);
		{
			K_Engine::Entity* platform = entMan->addEntity();
			K_Engine::Transform* t = platform->addComponent<K_Engine::Transform>(); t->setDimensions(5.f, 1.0f, 5.f);
			t->setPosition(2.8, 0.f, 0);
			t->setRotation(0, 0, 45);
			ColliderType boxType = ColliderType::CT_BOX;
			BodyType bodyType = BodyType::BT_STATIC;
			K_Engine::RigidBody* r = platform->addComponent<K_Engine::RigidBody>(boxType, bodyType, 0.0f, K_Engine::PhysicsManager::GetInstance()->getLayerValue(platformLayer), futureCollidesWith);
			r->setRestitution(0.8f);
			K_Engine::MeshRenderer* m = platform->addComponent<K_Engine::MeshRenderer>();
			m->setMesh("cube.mesh");
			m->setMaterial("K_Engine/PrototypeOrange");
		}

		{
			/*Entity* audio = entMan->addEntity();
			AudioSource* a = audio->addComponent<AudioSource>();
			//a->playSong("./assets/sounds/samba_UCM.ogg");
			a->playSoundEffect("./assets/sounds/clap.wav", -1);
			a->playSoundEffect("./assets/sounds/crash.wav", -1);
			a->playSoundEffect("./assets/sounds/accordion.wav", -1);
			a->setGeneralVolume(75);
			a->stopOneSoundEffect("./assets/sounds/clap.wav");
			a->playSoundEffect("./assets/sounds/clap.wav", -1);
			a->pauseOneSoundEffect("./assets/sounds/clap.wav");
			a->resumeOneSoundEffect("./assets/sounds/clap.wav");
			a->resumeOneSoundEffect("./assets/sounds/accordion.wav");*/

		}

		entMan->start();
	}
}
