#include "Scene.h"

#include <ecs_prj/EntityManager.h>
#include <ecs_prj/Entity.h>
#include <script_prj/ScriptManager.h>

// SOON TO BE DELETED
#include <physics_prj/PhysicsManager.h>
#include <physics_prj/CollisionLayers.h>

#include <render_prj/RenderManager.h>

#include <components_prj/Transform.h>
#include <components_prj/MeshRenderer.h>
#include <components_prj/RigidBody.h>
#include <components_prj/AudioSource.h>
#include <components_prj/Light.h>
#include <components_prj/Button.h>
#include <components_prj/Image.h>
#include <components_prj/ProgressBar.h>
#include <components_prj/ScrollBar.h>
#include <components_prj/Text.h>

#include <utils_prj/Vector3.h>

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

	void Scene::update(int frameTime) 
	{
		entMan->update(frameTime);
	};

	void Scene::fixedUpdate(int deltaTime)
	{
		entMan->fixedUpdate(deltaTime);
	}

	void Scene::debug()
	{
		//Test Lua
		scriptMan = K_Engine::ScriptManager::GetInstance();
		scriptMan->reloadLuaScript("test2");
		scriptMan->createPlayerbyLecture();


		entMan = new K_Engine::EntityManager(); // Entity Manager

		// example scene (pending of development)
		std::string playerLayer = "Player";
		std::string nothingLayer = "Nothing";
		std::string platformLayer = "Platform";

		int playerCollidesWith = K_Engine::PhysicsManager::GetInstance()->getLayerID(platformLayer);

		//SPHERE
		K_Engine::Entity* player = entMan->addEntity();
		{
			K_Engine::Transform* t = player->addComponent<K_Engine::Transform>(); t->setScale(3.0f);
			t->setPosition(0.5f, 8, 0);
			ColliderType boxType = ColliderType::CT_SPHERE;
			BodyType bodyType = BodyType::BT_DYNAMIC;
			float mass = 1.0f;
			RigidBody* r = player->addComponent<RigidBody>(boxType, bodyType, mass, K_Engine::PhysicsManager::GetInstance()->getLayerID(playerLayer), playerCollidesWith);
			r->setFriction(0.6f);
			r->setRestitution(1.2f);
			K_Engine::MeshRenderer* m = player->addComponent<K_Engine::MeshRenderer>();
			m->setMesh("sphere.mesh");
			m->setMaterial("K_Engine/PrototypeBlue");
			m->debug();
		}

		//SPHERE CHILD
		K_Engine::Entity* playerChild = entMan->addEntity();
		{
			K_Engine::Transform* t = playerChild->addComponent<K_Engine::Transform>(); t->setScale(1.0f);
			t->setPosition(7, 7, 0);
			//t->setRotation(0, 0, 10);
			ColliderType boxType = ColliderType::CT_SPHERE;
			BodyType bodyType = BodyType::BT_DYNAMIC;
			float mass = 1.0f;
			//RigidBody* r = playerChild->addComponent<RigidBody>(boxType, bodyType, mass, physicsMan->getLayerID(playerLayer), playerCollidesWith);
			//r->setFriction(0.6f);
			//r->setRestitution(1.2f);
			K_Engine::MeshRenderer* m = playerChild->addComponent<K_Engine::MeshRenderer>();
			m->setMesh("sphere.mesh");
			m->setMaterial("K_Engine/PrototypeWhite");
			//m->debug();
		}
		player->addChild(playerChild);

		//PLATFORM ROTATED
		int platformCollidesWith = K_Engine::PhysicsManager::GetInstance()->getLayerID(playerLayer);
		{
			K_Engine::Entity* platform = entMan->addEntity();
			K_Engine::Transform* t = platform->addComponent<K_Engine::Transform>(); t->setScale(5.f, 1.0f, 5.f);
			t->setPosition(-2.8, 0.f, 0);
			t->setRotation(0, 0, -45);
			ColliderType boxType = ColliderType::CT_BOX;
			BodyType bodyType = BodyType::BT_STATIC;
			K_Engine::RigidBody* r = platform->addComponent<K_Engine::RigidBody>(boxType, bodyType, 0.0f, K_Engine::PhysicsManager::GetInstance()->getLayerID(platformLayer), platformCollidesWith);
			r->setRestitution(0.8f);
			K_Engine::MeshRenderer* m = platform->addComponent<K_Engine::MeshRenderer>();
			m->setMesh("cube.mesh");
			m->setMaterial("K_Engine/PrototypeOrange");
		}
		
		//WALL
		int futureCollidesWith = K_Engine::PhysicsManager::GetInstance()->getLayerID(playerLayer);
		{
			K_Engine::Entity* platform = entMan->addEntity();
			K_Engine::Transform* t = platform->addComponent<K_Engine::Transform>(); t->setScale(5.f, 1.0f, 5.f);
			t->setPosition(5.8, 1.5f, 0);
			t->setRotation(0, 0, 90);
			ColliderType boxType = ColliderType::CT_BOX;
			BodyType bodyType = BodyType::BT_STATIC;
			K_Engine::RigidBody* r = platform->addComponent<K_Engine::RigidBody>(boxType, bodyType, 0.0f, K_Engine::PhysicsManager::GetInstance()->getLayerID(platformLayer), futureCollidesWith);
			r->setDimensions({ 0.2, 1, 1 });
			r->setOffset({ 0, -1.0/*0*/, 0});
			r->setRestitution(0.8f);
			K_Engine::MeshRenderer* m = platform->addComponent<K_Engine::MeshRenderer>();
			m->setMesh("cube.mesh");
			m->setMaterial("K_Engine/PrototypeGrey");
		}

		//GROUND
		{
			K_Engine::Entity* platform = entMan->addEntity();
			K_Engine::Transform* t = platform->addComponent<K_Engine::Transform>(); t->setScale(20.f, 1.0f, 20.f);
			t->setPosition(0, -3.f, 0);
			t->setRotation(0, 0, 0);
			ColliderType boxType = ColliderType::CT_BOX;
			BodyType bodyType = BodyType::BT_STATIC;
			K_Engine::RigidBody* r = platform->addComponent<K_Engine::RigidBody>(boxType, bodyType, 0.0f, K_Engine::PhysicsManager::GetInstance()->getLayerID(platformLayer), futureCollidesWith);
			r->setRestitution(0.8f);
			K_Engine::MeshRenderer* m = platform->addComponent<K_Engine::MeshRenderer>();
			m->setMesh("cube.mesh");
			m->setMaterial("K_Engine/PrototypeRed");
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

		//LIGHT
		{
			Entity* light = entMan->addEntity();
			Light* lComp = light->addComponent<Light>(LightType::SPOTLIGHT, true);
		}

		//UI Button
		{
			K_Engine::Entity* button = entMan->addEntity();
			K_Engine::Transform* t = button->addComponent<K_Engine::Transform>();
			K_Engine::Button* b = button->addComponent<K_Engine::Button>("F", "TestButton", "TestButton", "TestButton");
			t->setPosition(900, 5, 500);
			t->setScale(0.4, 1, 1);
		}

		//UI Image
		{
			K_Engine::Entity* image = entMan->addEntity();
			K_Engine::Transform* t = image->addComponent<K_Engine::Transform>();
			K_Engine::Image* i = image->addComponent<K_Engine::Image>("E", "Fino");
			t->setPosition(0, 0, 20);
		}

		////UI Progress Bar 1
		//{
		//	K_Engine::Entity* progressBar = entMan->addEntity();
		//	K_Engine::Transform* t = progressBar->addComponent<K_Engine::Transform>();
		//	K_Engine::ProgressBar* p = progressBar->addComponent<K_Engine::ProgressBar>("A", "GreenDefaultProgressBar");
		//	t->setPosition(10, 680, 100);
		//	t->setScale(300, 25, 1);
		//}

		////UI Progress Bar 2
		//{
		//	K_Engine::Entity* progressBar = entMan->addEntity();
		//	K_Engine::Transform* t = progressBar->addComponent<K_Engine::Transform>();
		//	K_Engine::ProgressBar* p = progressBar->addComponent<K_Engine::ProgressBar>("B", "DefaultProgressBar");
		//	t->setPosition(10, 680, 50);
		//	t->setScale(300, 25, 1);
		//}

		//UI ScrollBar
		{
			K_Engine::Entity* scrollBar = entMan->addEntity();
			K_Engine::Transform* t = scrollBar->addComponent<K_Engine::Transform>();
			K_Engine::ScrollBar* i = scrollBar->addComponent<K_Engine::ScrollBar>("C", "DefaultButton", 1, 100);
		}

		//UI Text
		{
			K_Engine::Entity* text = entMan->addEntity();
			K_Engine::Transform* t = text->addComponent<K_Engine::Transform>();
			K_Engine::Text* i = text->addComponent<K_Engine::Text>("D", "Fino senhores");
			t->setPosition(135, 10, 50);
		}

		entMan->start();
	}
}