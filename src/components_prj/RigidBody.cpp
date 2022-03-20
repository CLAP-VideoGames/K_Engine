#include "RigidBody.h"

#include <components_prj/Transform.h>

#include <ecs_prj/Entity.h>

#include <utils_prj/CustomVector3.h>

#include <physics_prj/PhysicsManager.h>
#include <physics_prj/DynamicsWorld.h>
#include <physics_prj/CollisionListener.h>
#include <btBulletDynamicsCommon.h>

//Required
std::string RigidBody::name = "RigidBody";

RigidBody::RigidBody(Entity* e) : Component("RigidBody", e) {
	name = id;
}

RigidBody::RigidBody(Entity* e, ColliderType type, BodyType bType, float mass) : Component("RigidBody", e) {
	name = id;
	type_ = type;
	bType_ = bType;
	mass_ = mass;
	friction_ = 0.3;
	restitution_ = 0.1f;
}

RigidBody::~RigidBody() {
	
}

std::string RigidBody::GetId(){
	return name;
}

void RigidBody::setTrigger(bool value) {
	isTrigger = value;
}

//In both of this methods 0=x 1=y 2=z
void RigidBody::setRotConstraints(int i, bool value) {
	rotationConstraints[i] = value;
}
void RigidBody::setTrasConstraints(int i, bool value) {
	traslationConstraints[i] = value;
}

void RigidBody::setRestitution(float value){
	restitution_ = value;
}

void RigidBody::setFriction(float value){
	friction_ = value;
}

void RigidBody::start(){
	transformRf_ = entity->getComponent<Transform>();
	world_ = PhysicsManager::GetInstance()->getWorld();
	
	btTransform_ = PhysicsManager::GetInstance()->createTransform(transformRf_->getPosition(), transformRf_->getRotation());
	CustomVector3 scale = transformRf_->getScale();
	btVector3 size = { (btScalar)scale.x, (btScalar)scale.y, (btScalar)scale.z };
	rb = world_->addRigidBody(type_, *btTransform_, size, bType_, mass_, restitution_, friction_, 0, 0);
}

void RigidBody::update(){
	btVector3 pos = rb->getWorldTransform().getOrigin();
	btScalar y;
	btScalar z;
	btScalar x;
	rb->getWorldTransform().getRotation().getEulerZYX(z, y, x);
	transformRf_->setPosition(pos.x(), pos.y(), pos.z());
	transformRf_->setRotation(x, y, z);
}

void RigidBody::debug(){

}
