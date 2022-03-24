#include "PhysicsManager.h"

#include <btBulletDynamicsCommon.h>
#include <LinearMath/btTransform.h>

#include <physics_prj/DynamicsWorld.h>
#include <physics_prj/CollisionLayers.h>
#include <utils_prj/KVector3.h>

namespace K_Engine {
	std::unique_ptr<PhysicsManager> PhysicsManager::instance = nullptr;

	PhysicsManager::PhysicsManager() = default;

	PhysicsManager::~PhysicsManager() = default;

	PhysicsManager* PhysicsManager::GetInstance() {
		return instance.get();
	}

	bool PhysicsManager::Init(int step, const KVector3& gravity = KVector3(0, -9.8f, 0)) {
		instance.reset(new PhysicsManager());
		btVector3 grav_ = { (btScalar)gravity.x, (btScalar)gravity.y, (btScalar)gravity.z };
		return instance.get()->initWorld(step, grav_);
	}

	bool PhysicsManager::initWorld(int step, btVector3 const& gravity) {
		bool succeed = true;
		try {
			colLayers_ = new CollisionLayers();
			this->gravity = new btVector3(gravity);
			dynamicsWorld_ = new DynamicsWorld(gravity);
			btWorld = dynamicsWorld_->getBtWorld();
		}
		catch (const std::exception&) {
			succeed = false;
		}

		return succeed;
	}

	bool PhysicsManager::releaseWorld() {
		bool succeed = true;
		try {
			delete gravity;
			delete dynamicsWorld_; dynamicsWorld_ = nullptr;
		}
		catch (const std::exception&) {
			succeed = false;
		}

		return succeed;
	}

	void PhysicsManager::update() {
		btWorld->stepSimulation(1.f / 60.f, 10);
		//print positions of all objects
		/*for (int j = btWorld->getNumCollisionObjects() - 1; j >= 0; j--) {
			btCollisionObject* obj = btWorld->getCollisionObjectArray()[j];
			btRigidBody* body = btRigidBody::upcast(obj);
			btTransform trans;
			if (body && body->getMotionState()) {
				body->getMotionState()->getWorldTransform(trans);
			}
			else {
				trans = obj->getWorldTransform();
			}
			btScalar y;
			btScalar z;
			btScalar x;
			trans.getRotation().getEulerZYX(y, x, z);
		}*/
	}

	void PhysicsManager::changeCollisionFiltering(btRigidBody* rb, int group, std::string name) {
		btBroadphaseProxy* proxy = rb->getBroadphaseProxy();
		proxy->m_collisionFilterGroup = group;
		proxy->m_collisionFilterMask = getLayerValue(name);
	}

	btTransform* PhysicsManager::createTransform(KVector3 const& position, KVector3 const& rotation) {
		btVector3 pos = { (btScalar)position.x, (btScalar)position.y, (btScalar)position.z };
		btVector3 rot = { (btScalar)btRadians(rotation.x), (btScalar)btRadians(rotation.y), (btScalar)btRadians(rotation.z) };

		btTransform* tr = new btTransform();
		tr->setIdentity();
		tr->setOrigin(pos);
		//tr->setBasis()
		tr->setRotation(btQuaternion(rot.x(), rot.y(), rot.z()));
		return tr;
	}

	void PhysicsManager::changeGravity(KVector3 const& gravity) {
		btVector3 grav_ = { (btScalar)gravity.x, (btScalar)gravity.y, (btScalar)gravity.z };

		if (this->gravity != nullptr) *this->gravity = grav_;
		else this->gravity = new btVector3(grav_);
	}

	DynamicsWorld* PhysicsManager::getWorld() const {
		return dynamicsWorld_;
	}

	int PhysicsManager::getLayerValue(std::string name) const {
		return colLayers_->getLayer(name);
	}

	void PhysicsManager::addLayer(std::string name){
		colLayers_->addLayer(name);
	}

	bool PhysicsManager::Shutdown() {
		bool exit = instance.get()->releaseWorld();
		instance.reset(nullptr);
		return exit;
	}
}