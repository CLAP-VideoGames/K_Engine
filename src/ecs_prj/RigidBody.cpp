#include "RigidBody.h"
#include "Entity.h"
#include <utils_prj/CustomVector3.h>
#include <ecs_prj/Transform.h>
#include <physics_prj/PhysicsManager.h>
#include <physics_prj/DynamicsWorld.h>
#include <physics_prj/CollisionListener.h>
#include <btBulletDynamicsCommon.h>

//Required
std::string RigidBody::name = "RigidBody";

RigidBody::RigidBody(Entity* e) : Component("RigidBody", nullptr) {
	name = id;
}

RigidBody::RigidBody(Entity* e, ColliderType type) : Component("RigidBody", nullptr) {
	name = id;
	type_ = type;
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

void RigidBody::start(){
	transformRf_ = entity->getComponent<Transform>();
	world_ = PhysicsManager::GetInstance()->getWorld();
	
	btTransform_ = PhysicsManager::GetInstance()->createTransform({0,0,0});
	CustomVector3 scale = transformRf_->getScale();
	btVector3 size = { (btScalar)scale.x, (btScalar)scale.y, (btScalar)scale.z };
	rb = world_->addRigidBody(type_, *btTransform_, size, 1.0f, 0, 0);
}

void RigidBody::update(){
	//transformRf_->setPosition();
}

void RigidBody::debug(){

}
