#include "RigidBody.h"
//Required
std::string RigidBody::name = "RigidBody";

RigidBody::RigidBody() : Component("RigidBody") {

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