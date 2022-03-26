#include "Engine.h"

#include <stdio.h>
#include <iostream>

//Just for testing
// this should be on the render project, before the SDL.h,
// but since it's here I put it there temporarily
#include <OgreLogManager.h>

#include <physics_prj/PhysicsManager.h>
#include <physics_prj/CollisionLayers.h>
#include <render_prj/RenderManager.h>
#include <sound_prj/AudioManager.h>
#include <input_prj/InputManager.h>
#include <ui_prj/UIManager.h>

#include <ecs_prj/EntityManager.h>
#include <ecs_prj/ComponentManager.h>
#include <ecs_prj/Entity.h>

#include <components_prj/Transform.h>
#include <components_prj/RigidBody.h>
#include <components_prj/MeshRenderer.h>
#include <components_prj/AudioSource.h>

#include <utils_prj/KTimer.h>
#include <utils_prj/KVector3.h>
#include <utils_prj/KMath.h>

#define DELTA_TIME 1.0/60.0

namespace K_Engine {
	Engine::Engine(std::string n) {
		name = n;
	}

	Engine::~Engine() = default;

	bool Engine::init() {
		// initialisation of all sub-engines
		bool success = K_Engine::RenderManager::Init(name + "Render") &&
			K_Engine::PhysicsManager::Init(20, { 0, -9.8, 0 }) &&
			K_Engine::UIManager::Init(name + "UI") &&
			K_Engine::AudioManager::Init() &&
			K_Engine::InputManager::Init() &&
			K_Engine::ComponentManager::Init(name + "Components");

		// if something goes wrong, we exit initialization
		if (!success) return false;

		// acquisition of sub-engine's instances
		renderMan = K_Engine::RenderManager::GetInstance();
		physicsMan = K_Engine::PhysicsManager::GetInstance();
		uiMan = K_Engine::UIManager::GetInstance();
		audioMan = K_Engine::AudioManager::GetInstance();
		inputMan = K_Engine::InputManager::GetInstance();
		compMan = K_Engine::ComponentManager::GetInstance();
	}

	void Engine::setup()
	{
		// physics setup
		std::string playerLayer = "Player";
		std::string nothingLayer = "Nothing";
		std::string platformLayer = "Platform";

		physicsMan->addLayer(playerLayer);
		physicsMan->addLayer(nothingLayer);
		physicsMan->addLayer(platformLayer);

		// input setup
		inputMan->setDeathZones(5000, 0);

		// base components setup
		compMan->add<K_Engine::Transform>();
		compMan->add<K_Engine::MeshRenderer>();
		compMan->add<K_Engine::RigidBody>();
		compMan->add<K_Engine::AudioSource>();

		// THIS SHOULD BE DELETED EVENTUALLY UPON ENGINE RELEASE
		debug();

		// start components
		entMan->start();
	}

	void Engine::run()
	{
		// Timer for main loop
		K_Engine::KTimer timer = K_Engine::KTimer();

		bool run = true; // time --> miliseconds
		unsigned int accFrameTime = 0, currTime = timer.currTime();
		while (run) {
			unsigned int frame = timer.currTime() - currTime;
			currTime += frame;

			accFrameTime += frame;
			while (accFrameTime >= DELTA_TIME) {
				inputMan->update();

				run = (!inputMan->controllerButtonPressed(K_Engine::CONTROLLER_BUTTON_B)
					&& !inputMan->isKeyDown(K_Engine::SCANCODE_ESCAPE));

				if (inputMan->isKeyDown(K_Engine::SCANCODE_0)) {
					K_Engine::KVector3 scal = t->getScale();
					t->setScale(3, 3, 3);
				}

				//Physics update
				entMan->fixedUpdate();
				physicsMan->update();
				accFrameTime -= DELTA_TIME;
			}
			//Regular update for the entities
			entMan->update();
			uiMan->update();
			renderMan->render();
		}
	}

	bool Engine::shutdown()
	{
		delete entMan;

		return K_Engine::AudioManager::Shutdown() &&
			K_Engine::UIManager::Shutdown() &&
			K_Engine::PhysicsManager::Shutdown() &&
			K_Engine::RenderManager::Shutdown();
	}

	void Engine::debug()
	{
		// ui debug
		uiMan->debug();

		//uiMan->createSlider(std::pair<float, float>(0.2f, 0.2f), std::pair<float, float>(0.1f, 0.1f));
		//uiMan->createScrollbar(std::pair<float, float>(0.7f, 0.7f), std::pair<float, float>(0.1f, 0.1f));
		//uiMan->addText("Hola", std::pair<float, float>(0, 0));
		//CEGUI::ProgressBar* pr = uiMan->addProgressBar(std::pair<float, float>(0.5, 0.5), std::pair<float, float>(0.3, 0.1));
		//uiMan->addButton("BUTTON", std::pair<float, float>(0.5, 0.5), td::pair<float, float>(0.3, 0.1));
		//uiMan->exampleUI();

		entMan = new K_Engine::EntityManager(); // Entity Manager

		// example scene (pending of development)
		std::string playerLayer = "Player";
		std::string nothingLayer = "Nothing";
		std::string platformLayer = "Platform";

		int playerCollidesWith = physicsMan->getLayerValue(platformLayer);
		//Configurations Scope
		K_Engine::Entity* player = entMan->addEntity();
		t = player->addComponent<K_Engine::Transform>(); t->setDimensions(3.0f);
		{
			t->setPosition(3, 3, 0);
			ColliderType boxType = ColliderType::CT_SPHERE;
			BodyType bodyType = BodyType::BT_DYNAMIC;
			float mass = 1.0f;
			//RigidBody* r = player->addComponent<RigidBody>(boxType, bodyType, mass, physicsMan->getLayerValue(playerLayer), playerCollidesWith);
			//r->setFriction(0.6f);
			//r->setRestitution(1.2f);
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

		int platformCollidesWith = physicsMan->getLayerValue(playerLayer);
		//Configurations Scope
		{
			K_Engine::Entity* platform = entMan->addEntity();
			K_Engine::Transform* t = platform->addComponent<K_Engine::Transform>(); t->setDimensions(5.f, 1.0f, 5.f);
			t->setPosition(-2.8, 0.f, 0);
			t->setRotation(0, 0, -45);
			ColliderType boxType = ColliderType::CT_BOX;
			BodyType bodyType = BodyType::BT_STATIC;
			K_Engine::RigidBody* r = platform->addComponent<K_Engine::RigidBody>(boxType, bodyType, 0.0f, physicsMan->getLayerValue(platformLayer), platformCollidesWith);
			r->setRestitution(0.8f);
			K_Engine::MeshRenderer* m = platform->addComponent<K_Engine::MeshRenderer>();
			m->setMesh("cube.mesh");
			m->setMaterial("K_Engine/PrototypeOrange");
		}

		int futureCollidesWith = physicsMan->getLayerValue(playerLayer);
		{
			K_Engine::Entity* platform = entMan->addEntity();
			K_Engine::Transform* t = platform->addComponent<K_Engine::Transform>(); t->setDimensions(5.f, 1.0f, 5.f);
			t->setPosition(2.8, 0.f, 0);
			t->setRotation(0, 0, 45);
			ColliderType boxType = ColliderType::CT_BOX;
			BodyType bodyType = BodyType::BT_STATIC;
			K_Engine::RigidBody* r = platform->addComponent<K_Engine::RigidBody>(boxType, bodyType, 0.0f, physicsMan->getLayerValue(platformLayer), futureCollidesWith);
			r->setRestitution(0.8f);
			K_Engine::MeshRenderer* m = platform->addComponent<K_Engine::MeshRenderer>();
			m->setMesh("cube.mesh");
			m->setMaterial("K_Engine/PrototypeOrange");
		}

		{
			Entity* audio = entMan->addEntity();
			AudioSource* a = audio->addComponent<AudioSource>();
			//a->playSong("./assets/sounds/samba_UCM.ogg");
			a->playSoundEffect("./assets/sounds/clap.wav", -1);
			a->setGeneralVolume(35);
			a->stopOneSoundEffect("./assets/sounds/clap.wav");
		}
	}
}