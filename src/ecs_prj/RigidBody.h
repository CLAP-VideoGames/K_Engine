#pragma once
#ifndef RIGIDBODY_H
#define RIGIDBODY_H

#include <ecs_prj/Component.h>

class btCollisionShape;
class btRigidBody;
class btDefaultMotionState;
class RigidBodyState;
class Transform;

class RigidBody : public Component
{
public:
	RigidBody();
	~RigidBody();

	//Required method for the component name
	static std::string getId() { return name; }

	void setTrigger(bool value);

	void setRotConstraints(int i, bool value);
	void setTrasConstraints(int i, bool value);

private:
	Transform* transformRf_;
	
	//Boolean to control if the associated trigger is a trigger or not (default is false)
	bool isTrigger = false;

	//Reference to bullet rigidbody
	btRigidBody* rb = nullptr;
	//Reference to the collision shape of this rigidbody
	btCollisionShape* rbShape = nullptr;
	//Reference to the default motion state of this rigidbody
	RigidBodyState* rbState = nullptr;

	//Required
	static std::string name;

	//Array of constrains for rotation in x y z
	bool rotationConstraints[3]{ false, false, false };

	//Array of constrains for traslation in x y z
	bool traslationConstraints[3]{ false, false, false };
};
#endif // RIGIDBODY_H