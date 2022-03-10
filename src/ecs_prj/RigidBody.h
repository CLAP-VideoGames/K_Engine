#pragma once
#include "Component.h"

class btCollisionShape;
class btRigidBody;
class btDefaultMotionState;

namespace BtOgre {
	class RigidBody;
}

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

protected:


private:
	BtOgre::RigidBody* rb;

	//Boolean to control if the associated trigger is a trigger or not (default is false)
	bool isTrigger = false;

	//Reference to bullet rigidbody
	btRigidBody* bulletRigidBody = nullptr;
	
	//Reference to the collision shape of this rigidbody
	btCollisionShape* bulletCollisionShape = nullptr;

	//Reference to the default motion state of this rigidbody
	btDefaultMotionState* bulletDefMotionState = nullptr;

	//Required
	static std::string name;

	//Array of constrains for rotation in x y z
	bool rotationConstraints[3]{ false, false, false };

	//Array of constrains for traslation in x y z
	bool traslationConstraints[3]{ false, false, false };
};