#include "RigidBody.h"
#include "Entity.h"
#include <physics_prj/PhysicsManager.h>
#include <ecs_prj/Transform.h>
//Required
std::string RigidBody::name = "RigidBody";

RigidBody::RigidBody() : Component("RigidBody", nullptr) {
	name = id;
	transformRf_ = entity->getComponent<Transform>();
}

RigidBody::~RigidBody() {
	
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

void RigidBody::update(){
	//transformRf_->setPosition();
}
