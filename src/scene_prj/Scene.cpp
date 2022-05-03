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
		//loadScene(nameMap);

		//PedroPablo
		K_Engine::Entity* suelo = entMan->addEntity();
		{
			K_Engine::Transform* t = suelo->addComponent<K_Engine::Transform>();
			t->setPosition(0, 10, 0);
			K_Engine::MeshRenderer* m = suelo->addComponent<K_Engine::MeshRenderer>();
			m->setMesh("cubeMap.mesh");
			K_Engine::RigidBody* r = suelo->addComponent<K_Engine::RigidBody>(ColliderType::CT_BOX, BodyType::BT_STATIC, 10, 1, 1);
			float scaleFa = 10.0f;
			r->setDimensions({ scaleFa, scaleFa, scaleFa });

		}

		//PedroPablo
		K_Engine::Entity* monkey = entMan->addEntity();
		{
			K_Engine::Transform* t = monkey->addComponent<K_Engine::Transform>();
			float scale = 1.5f;
			t->setScale(scale);
			t->setPosition(0, 39, 0);


			t->setRotation(0, 0, 0);
			K_Engine::MeshRenderer* m = monkey->addComponent<K_Engine::MeshRenderer>();
				m->setMesh("Generic.mesh");
			m->debug();

			K_Engine::RigidBody* r = monkey->addComponent<K_Engine::RigidBody>(ColliderType::CT_BOX, BodyType::BT_DYNAMIC, 50, 1, 1);
			r->setDimensions({ 2, 5, 2});
			r->setOffset({0, 3, 0});
			r->setFriction(0.8f);
			
			r->setPosConstraints({1, 1, 0});
			r->setRotConstraints({0, 0, 0});
		}
		K_Engine::Animator* anim_ = monkey->addComponent<K_Engine::Animator>();

		//LIGHT
		{
			Entity* light = entMan->addEntity();
			K_Engine::Transform* t = light->addComponent<K_Engine::Transform>();
			t->setPosition(0, 20, 20);
			Light* lComp = light->addComponent<Light>(LightType::DIRECTIONAL, true, new Vector3(1, 1, 1), new Vector3(0, 0, 0));
		}

		K_Engine::RenderManager::GetInstance()->getCamera()->setCameraPos(0, 20, 100);

		//SPHERE
		/*K_Engine::Entity* player = entMan->addEntity();
		{
			K_Engine::Transform* t = player->addComponent<K_Engine::Transform>(); t->setScale(3.0f);
			t->setPosition(0.5f, 8, 0);
			t->debug();
			ColliderType boxType = ColliderType::CT_SPHERE;
			BodyType bodyType = BodyType::BT_DYNAMIC;
			float mass = 1.0f;
			RigidBody* r = player->addComponent<RigidBody>(boxType, bodyType, mass, K_Engine::PhysicsManager::GetInstance()->getLayerID(platformLayer), playerCollidesWith);
			r->setFriction(0.6f);
			r->setRestitution(1.2f);
			K_Engine::MeshRenderer* m = player->addComponent<K_Engine::MeshRenderer>();
			m->setMesh("sphere.mesh");
			m->setMaterial("K_Engine/PrototypeBlue");
			m->debug();
		}*/

		////SPHERE CHILD
		//K_Engine::Entity* playerChild = entMan->addEntity();
		//{
		//	K_Engine::Transform* t = playerChild->addComponent<K_Engine::Transform>(); t->setScale(1.0f);
		//	t->setPosition(7, 7, 0);
		//	//t->setRotation(0, 0, 10);
		//	ColliderType boxType = ColliderType::CT_SPHERE;
		//	BodyType bodyType = BodyType::BT_DYNAMIC;
		//	float mass = 1.0f;
		//	//RigidBody* r = playerChild->addComponent<RigidBody>(boxType, bodyType, mass, physicsMan->getLayerID(playerLayer), playerCollidesWith);
		//	//r->setFriction(0.6f);
		//	//r->setRestitution(1.2f);
		//	K_Engine::MeshRenderer* m = playerChild->addComponent<K_Engine::MeshRenderer>();
		//	m->setMesh("sphere.mesh");
		//	m->setMaterial("K_Engine/PrototypeWhite");
		//	//m->debug();
		//}
		//player->addChild(playerChild);

		////PLATFORM ROTATED
		//int platformCollidesWith = K_Engine::PhysicsManager::GetInstance()->getLayerID(playerLayer);
		//{
		//	K_Engine::Entity* platform = entMan->addEntity();
		//	K_Engine::Transform* t = platform->addComponent<K_Engine::Transform>(); t->setScale(5.f, 1.0f, 5.f);
		//	t->setPosition(-2.8, 0.f, 0);
		//	t->setRotation(0, 0, -45);
		//	ColliderType boxType = ColliderType::CT_BOX;
		//	BodyType bodyType = BodyType::BT_STATIC;
		//	K_Engine::RigidBody* r = platform->addComponent<K_Engine::RigidBody>(boxType, bodyType, 0.0f, K_Engine::PhysicsManager::GetInstance()->getLayerID(platformLayer), platformCollidesWith);
		//	r->setRestitution(0.8f);
		//	K_Engine::MeshRenderer* m = platform->addComponent<K_Engine::MeshRenderer>();
		//	m->setMesh("cube.mesh");
		//	m->setMaterial("K_Engine/PrototypeOrange");
		//}
		//
		////WALL
		//int futureCollidesWith = K_Engine::PhysicsManager::GetInstance()->getLayerID(playerLayer);
		//{
		//	K_Engine::Entity* platform = entMan->addEntity();
		//	K_Engine::Transform* t = platform->addComponent<K_Engine::Transform>(); t->setScale(5.f, 1.0f, 5.f);
		//	t->setPosition(5.8, 1.5f, 0);
		//	t->setRotation(0, 0, 90);
		//	ColliderType boxType = ColliderType::CT_BOX;
		//	BodyType bodyType = BodyType::BT_STATIC;
		//	K_Engine::RigidBody* r = platform->addComponent<K_Engine::RigidBody>(boxType, bodyType, 0.0f, K_Engine::PhysicsManager::GetInstance()->getLayerID(platformLayer), futureCollidesWith);
		//	r->setDimensions({ 0.2, 1, 1 });
		//	r->setOffset({ 0, -1.0/*0*/, 0});
		//	r->setRestitution(0.8f);
		//	K_Engine::MeshRenderer* m = platform->addComponent<K_Engine::MeshRenderer>();
		//	m->setMesh("cube.mesh");
		//	m->setMaterial("K_Engine/PrototypeGrey");
		//}

		////GROUND
		//{
		//	K_Engine::Entity* platform = entMan->addEntity();
		//	K_Engine::Transform* t = platform->addComponent<K_Engine::Transform>();
		//	t->setPosition(0, -0.5f, 0);
		//	ColliderType boxType = ColliderType::CT_BOX;
		//	BodyType bodyType = BodyType::BT_STATIC;
		//	K_Engine::RigidBody* r = platform->addComponent<K_Engine::RigidBody>(boxType, bodyType, 0.0f, 1, 1);
		//	r->setDimensions({ 10, 1.69 ,10});
		//	r->setRestitution(0.8f);
		//	K_Engine::MeshRenderer* m = platform->addComponent<K_Engine::MeshRenderer>();
		//	m->setMesh("cubo.mesh");
		//	m->setMaterial("ground");
		//}

		////PedroPablo
		//K_Engine::Entity* monkey = entMan->addEntity();
		//{
		//	K_Engine::Transform* t = monkey->addComponent<K_Engine::Transform>();
		//	float scale = 0.5f;
		//	t->setScale(scale);
		//	t->setPosition(0, 5, 5);
		//	//t->rotate(0,-90, 0);
		//	K_Engine::MeshRenderer* m = monkey->addComponent<K_Engine::MeshRenderer>();
		//	m->setMesh("PedroPablo.mesh");
		//	m->debug();
		//}
		//K_Engine::Animator* anim = monkey->addComponent<K_Engine::Animator>();

		////Dario
		//K_Engine::Entity* monkey2 = entMan->addEntity();
		//{
		//	K_Engine::Transform* t = monkey2->addComponent<K_Engine::Transform>();
		//	float scale = 0.5f;
		//	t->setScale(scale);
		//	t->setPosition(-3, 5, 5);
		//	t->rotate(0,90, 0);
		//	K_Engine::MeshRenderer* m = monkey2->addComponent<K_Engine::MeshRenderer>();
		//	m->setMesh("Dario.mesh");
		//	m->debug();
		//}
		//K_Engine::Animator* anim_ = monkey2->addComponent<K_Engine::Animator>();

		//{
		//	Entity* audio = entMan->addEntity();
		//	AudioSource* a = audio->addComponent<AudioSource>(AudioType::MUSIC, "assets/sounds/samba_UCM.ogg", 1.f, true, true);
		//}

		////LIGHT
		//{
		//	Entity* light = entMan->addEntity();
		//	K_Engine::Transform* t = light->addComponent<K_Engine::Transform>();
		//	t->setPosition(0, 20, 20);
		//	Light* lComp = light->addComponent<Light>(LightType::DIRECTIONAL, true, new Vector3(1, 1, 1), new Vector3(0, 0, 0));
		//}

		////UI Button
		//{
		//	K_Engine::Entity* button = entMan->addEntity();
		//	K_Engine::Transform* t = button->addComponent<K_Engine::Transform>();
		//	K_Engine::Button* b = button->addComponent<K_Engine::Button>("F", "TestButton", "TestButton", "TestButton");
		//	t->setPosition(900, 5, 500);
		//	t->setScale(0.4, 1, 1);
		//}

		////UI Image
		//{
		//	K_Engine::Entity* image = entMan->addEntity();
		//	K_Engine::Transform* t = image->addComponent<K_Engine::Transform>();
		//	K_Engine::Image* i = image->addComponent<K_Engine::Image>("E", "Fino");
		//	t->setPosition(0, 0, 20);
		//}

		////UI Progress Bar 1
		//{
		//	K_Engine::Entity* progressBar = entMan->addEntity();
		//	K_Engine::Transform* t = progressBar->addComponent<K_Engine::Transform>();
		//	K_Engine::ProgressBar* p = progressBar->addComponent<K_Engine::ProgressBar>("A", "GreenDefaultProgressBar", 200, 100, 500, 150);
		//	t->setPosition(10, 680, 100);
		//	t->setScale(300, 25, 1);
		//}

		////UI Progress Bar 2
		//{
		//	K_Engine::Entity* progressBar = entMan->addEntity();
		//	K_Engine::Transform* t = progressBar->addComponent<K_Engine::Transform>();
		//	K_Engine::ProgressBar* p = progressBar->addComponent<K_Engine::ProgressBar>("B", "DefaultProgressBar", 100, 500, 300, 50);
		//	t->setPosition(10, 680, 50);
		//	t->setScale(300, 25, 1);
		//}

		//UI Text
		/*{
			K_Engine::Entity* text = entMan->addEntity();
			K_Engine::Transform* t = text->addComponent<K_Engine::Transform>();
			K_Engine::Text* i = text->addComponent<K_Engine::Text>("D", "MyFont", 60, "Fino senhores", Vector3(1, 0, 0));
			i->changeText("Tremendo, senhores");
			t->setPosition(135, 10, 50);
		}*/

		////UI Slider
		//{
		//	K_Engine::Entity* slider = entMan->addEntity();
		//	K_Engine::Transform* t = slider->addComponent<K_Engine::Transform>();
		//	K_Engine::Slider* i = slider->addComponent<K_Engine::Slider>("G", "DefaultButton", 40, 200, 300);
		//}

		//Awake of the entities
		entMan->awake();
		//First onEnable
		entMan->onEnable();
		//Start of the entites
		entMan->start();

		anim_->playAnim("Jump_Generic");
		//anim->playAnim("Death");
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