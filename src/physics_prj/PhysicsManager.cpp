#include "PhysicsManager.h"

#include <btBulletDynamicsCommon.h>
#include <LinearMath/btTransform.h>

#include <physics_prj/DynamicsWorld.h>
#include <physics_prj/CollisionLayers.h>

#include <log_prj/LogManager.h>

#include <utils_prj/Vector3.h>

namespace K_Engine {
	std::unique_ptr<PhysicsManager> PhysicsManager::instance = nullptr;

	PhysicsManager::PhysicsManager() = default;

	PhysicsManager::~PhysicsManager() = default;

	PhysicsManager* PhysicsManager::GetInstance() {
		return instance.get();
	}

	bool PhysicsManager::Init() {
		try {
			instance.reset(new PhysicsManager());
			const Vector3& gravity = Vector3(0, -60.8f, 0);
			btVector3 grav_ = { (btScalar)gravity.x, (btScalar)gravity.y, (btScalar)gravity.z };
			instance.get()->initWorld(grav_);
		}
		catch (const std::exception& e) {
			return K_Engine::LogManager::GetInstance()->addLog(K_Engine::LogType::FATAL, e.what());
		}

		return K_Engine::LogManager::GetInstance()->addLog(K_Engine::LogType::INFO, "Physics manager initialization success");
	}

	bool PhysicsManager::Shutdown() {
		try {
			instance.get()->releaseWorld();
			instance.reset(nullptr);
		}
		catch (const std::exception& e) {
			return K_Engine::LogManager::GetInstance()->addLog(K_Engine::LogType::FATAL, e.what());
		}

		return K_Engine::LogManager::GetInstance()->addLog(K_Engine::LogType::INFO, "Physics manager shutdown success");
	}

	void PhysicsManager::update() {
		btWorld->stepSimulation(1.f / 60.f, 10);

		dynamicsWorld_->getBtWorld()->getDebugDrawer()->setDebugMode(3);
		dynamicsWorld_->getBtWorld()->debugDrawWorld();
	}

	void PhysicsManager::registerDefaultLayers() {
		addLayer("All");
		addLayer("Default");
	}

	void PhysicsManager::initWorld(btVector3 const& gravity) {
		colLayers_ = new CollisionLayers();
		this->gravity = new btVector3(gravity);
		dynamicsWorld_ = new DynamicsWorld(gravity);
		btWorld = dynamicsWorld_->getBtWorld();
	}

	void PhysicsManager::addLayer(std::string name) {
		colLayers_->addLayer(name);
	}

	void PhysicsManager::releaseWorld() {
		delete colLayers_; colLayers_ = nullptr;
		delete gravity; gravity = nullptr;
		delete dynamicsWorld_; dynamicsWorld_ = nullptr;
	}

	void PhysicsManager::changeCollisionFiltering(btRigidBody* rb, int group, std::string name) {
		btBroadphaseProxy* proxy = rb->getBroadphaseProxy();
		proxy->m_collisionFilterGroup = group;
		proxy->m_collisionFilterMask = getLayerID(name);
	}

	btTransform* PhysicsManager::createTransform(Vector3 const& position, Vector3 const& offset, Vector3 const& rotation) {
		btVector3 pos = { (btScalar)position.x, (btScalar)position.y, (btScalar)position.z };
		btVector3 off = { (btScalar)offset.x, (btScalar)offset.y, (btScalar)offset.z };
		btVector3 rot = { (btScalar)btRadians(rotation.x), (btScalar)btRadians(rotation.y), (btScalar)btRadians(rotation.z) };

		btTransform* tr = new btTransform();
		tr->setIdentity();
		tr->setOrigin(pos + off);
		//tr->setBasis()
		tr->setRotation(btQuaternion(rot.x(), rot.y(), rot.z()));
		return tr;
	}

	void PhysicsManager::setGravity(Vector3 const& gravity) {
		btVector3 grav_ = { (btScalar)gravity.x, (btScalar)gravity.y, (btScalar)gravity.z };

		if (this->gravity != nullptr) {
			btWorld->setGravity(grav_);
			*this->gravity = grav_;
		}
		else {
			btWorld->setGravity(grav_);
			this->gravity = new btVector3(grav_);
		}
	}

	DynamicsWorld* PhysicsManager::getWorld() const {
		return dynamicsWorld_;
	}

	int PhysicsManager::getLayerID(std::string name) const {
		return colLayers_->getLayer(name);
	}

	void PhysicsManager::registerDebugDrawer(btIDebugDraw* dB) {
		dynamicsWorld_->getBtWorld()->setDebugDrawer(dB);
	}
}