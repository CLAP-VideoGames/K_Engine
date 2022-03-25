#include "RigidBody.h"

#include <components_prj/Transform.h>

#include <ecs_prj/Entity.h>

#include <utils_prj/KVector3.h>

#include <physics_prj/PhysicsManager.h>
#include <physics_prj/DynamicsWorld.h>
#include <physics_prj/CollisionListener.h>
#include <btBulletDynamicsCommon.h>

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
	rb = world_->addRigidBody(type_, *btTransform_, dimensions_, scale_, bType_, mass_, restitution_, friction_, group_, mask_);
}

void RigidBody::update() {
	btVector3 pos = rb->getWorldTransform().getOrigin();
	btScalar y;
	btScalar z;
	btScalar x;
	rb->getWorldTransform().getRotation().getEulerZYX(z, y, x);

	//Before we set the new position we recalculate the children positions
	std::vector<Entity*> children = entity->getChildren();
	for (auto c : children) {
		//Data for the calculation
		Transform* childT = c->getComponent<Transform>();

		KVector3 childPos = childT->getPosition();
		KVector3 childRot = childT->getRotation();

		KVector3 oldParentPos = entity->getComponent<Transform>()->getPosition();
		KVector3 oldParentRot = entity->getComponent<Transform>()->getRotation();

		KVector3 toAdd;
		KVector3 rotToAdd;

		//Set to the new pos because we dont have a converter to btVector3
		toAdd.x = pos.x();
		toAdd.y = pos.y();
		toAdd.z = pos.z();

		//Set to the new rot because we btScalar
		rotToAdd.x = x;
		rotToAdd.y = y;
		rotToAdd.z = z;

		//Get the diference between new pos and oldPos
		toAdd.x -= oldParentPos.x;
		toAdd.y -= oldParentPos.y;
		toAdd.z -= oldParentPos.z;

		//Get the diference between new rot and oldRot
		rotToAdd.x -= oldParentRot.x;
		rotToAdd.y -= oldParentRot.y;
		rotToAdd.z -= oldParentRot.z;

		//Set its new position with the parent as (0,0,0)
		childT->setPosition(childPos.x + toAdd.x, childPos.y + toAdd.y, childPos.z + toAdd.z);
		//Set its new rotation acording to its parent
		childT->setRotation(childRot.x + rotToAdd.x, childRot.y + rotToAdd.y, childRot.z + rotToAdd.z);
	}

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
