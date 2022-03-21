#pragma once
#ifndef RIGIDBODY_H
#define RIGIDBODY_H

#include <ecs_prj/Component.h>

class btCollisionShape;
class btRigidBody;
class btTransform;
class btDefaultMotionState;
class DynamicsWorld;

class RigidBodyState;
class Transform;
enum class ColliderType;
enum class BodyType;

class RigidBody : public Component
{
public:
	//Required Contructor so the component is initialized properly
	RigidBody(Entity* e);
	RigidBody(Entity* e,ColliderType type_, BodyType bType_, float mass, int group_ = 1, int mask_ = 1);
	~RigidBody();

	//Required method for the component name
	static std::string GetId();

	void setTrigger(bool value);

	void setRotConstraints(int i, bool value);
	void setTrasConstraints(int i, bool value);

	void setRestitution(float value);
	void setFriction(float value);

	virtual void start();
	virtual void update();
	virtual void debug();

	void syncScale();

private:
	//Reference to transform Component
	Transform* transformRf_ = nullptr;
	//Mesh Type of the body
	ColliderType type_;
	//Body Physics Type
	BodyType bType_;
	//Reference to the world
	DynamicsWorld* world_ = nullptr;
	//Boolean to control if the associated trigger is a trigger or not (default is false)
	bool isTrigger = false;
	//Mass of the body
	float mass_;
	//Reference to bullet rigidbody
	btRigidBody* rb = nullptr;
	//Reference to the collision shape of this rigidbody
	btCollisionShape* rbShape = nullptr;
	//Reference to the default motion state of this rigidbody
	RigidBodyState* rbState = nullptr;
	//Reference to the physics transform of this rigidbody
	btTransform* btTransform_ = nullptr;
	//Required
	static std::string name;

	float restitution_;
	
	float friction_;
	//Array of constrains for rotation in x y z
	bool rotationConstraints[3]{ false, false, false };

	//Array of constrains for traslation in x y z
	bool traslationConstraints[3]{ false, false, false };

	//Collision filtering
	int group_;
	int mask_;
};
#endif // RIGIDBODY_H