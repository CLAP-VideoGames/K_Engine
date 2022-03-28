#include "RigidBody.h"

#include <components_prj/Transform.h>

#include <ecs_prj/Entity.h>

#include <utils_prj/KVector3.h>

#include <physics_prj/PhysicsManager.h>
#include <physics_prj/DynamicsWorld.h>
#include <physics_prj/CollisionListener.h>
#include <btBulletDynamicsCommon.h>

#include <iostream>
#include "utils_prj/CollisionCallbacks.h"

namespace K_Engine {
	//Required
	std::string RigidBody::name = "RigidBody";

	RigidBody::RigidBody(Entity* e) : Component("RigidBody", e) {
		name = id;
	}

	RigidBody::RigidBody(Entity* e, ColliderType type, BodyType bType, float mass, int mask, int group) : Component("RigidBody", e) {
		name = id;
		type_ = type;
		bType_ = bType;
		mass_ = mass;
		friction_ = 0.3;
		restitution_ = 0.1f;

		group_ = group;
		mask_ = mask;
	}

	RigidBody::~RigidBody() {

	}

	std::string RigidBody::GetId() {
		return name;
	}

	void RigidBody::setTrigger(bool value) {
		isTrigger = value;
	}

	//In both of this methods 0=x 1=y 2=z
	void RigidBody::setRotConstraints(int i, bool value) {
		rotationConstraints[i] = value;
	}
	void RigidBody::setPosConstraints(int i, bool value) {
		positionConstraints[i] = value;
	}

	void RigidBody::setRestitution(float value) {
		restitution_ = value;
	}

	void RigidBody::setFriction(float value) {
		friction_ = value;
	}

	void RigidBody::start() {
		transformRf_ = entity->getComponent<Transform>();
		world_ = K_Engine::PhysicsManager::GetInstance()->getWorld();

		btTransform_ = K_Engine::PhysicsManager::GetInstance()->createTransform(transformRf_->getPosition(), transformRf_->getRotation());
		KVector3 dimensions = transformRf_->getDimensions();
		KVector3 scale = transformRf_->getScale();
		btVector3 scale_ = { (btScalar)scale.x, (btScalar)scale.y, (btScalar)scale.z };
		btVector3 dimensions_ = { (btScalar)dimensions.x, (btScalar)dimensions.y, (btScalar)dimensions.z };
		K_Engine::CollisionInfo* colision = new K_Engine::CollisionInfo(this->entity,
			//Collision Enter Callback
			[=](void* other) {
				this->launchEnterCallbacks(other);
			},
			//Collision Stay Callback
				[=](void* other) {
				this->launchStayCallbacks(other);
			},
				//Collision Exit Callback
				[=](void* other) {
				this->launchExitCallbacks(other);
			});
		rb = world_->addRigidBody(type_, *btTransform_, dimensions_, scale_, bType_, mass_, restitution_, friction_, group_, mask_, colision);
	}

	void RigidBody::update() {
		btVector3 pos = rb->getWorldTransform().getOrigin();
		btScalar y;
		btScalar z;
		btScalar x;
		rb->getWorldTransform().getRotation().getEulerZYX(z, y, x);

		//set new position
		transformRf_->setPosition(pos.x(), pos.y(), pos.z());
		transformRf_->setRotation(x, y, z);
	}

	void RigidBody::debug() {

	}

	void RigidBody::syncScale() {
		KVector3 scale = transformRf_->getScale();
		btVector3 scale_ = { (btScalar)scale.x, (btScalar)scale.y, (btScalar)scale.z };
		world_->scaleCollisionShape(rb, scale_);
	}

	void RigidBody::launchEnterCallbacks(void* entity)
	{
		Entity* otherEntity = (Entity*)entity;
		colisionando = true;
		/*std::cout << "Entro\n";*/


	}

	void RigidBody::launchStayCallbacks(void* entity)
	{
		Entity* otherEntity = (Entity*)entity;
		if (colisionando) {
			/*std::cout << "Estoy\n";*/

		}
	}

	void RigidBody::launchExitCallbacks(void* entity)
	{
		Entity* otherEntity = (Entity*)entity;
		colisionando = false;
		/*std::cout << "Salgo\n";*/


	}
}