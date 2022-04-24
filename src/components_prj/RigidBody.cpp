#include "RigidBody.h"

#include <iostream>

#include <btBulletDynamicsCommon.h>
#include <components_prj/Transform.h>

#include <ecs_prj/Entity.h>

#include <physics_prj/PhysicsManager.h>
#include <physics_prj/DynamicsWorld.h>
#include <physics_prj/CollisionListener.h>

#include <utils_prj/Vector3.h>
#include <utils_prj/CollisionCallbacks.h>
#include <utils_prj/checkML.h>
#include <utils_prj/K_Map.h>

namespace K_Engine {
	//Required
	std::string RigidBody::name = "RigidBody";

	RigidBody::RigidBody() : Component() {
		friction_ = 0.3;
		restitution_ = 0.1f;
		group_ = 1;
		mask_ = 1;
		dimensions_ = new Vector3(1, 1, 1); //By default
		offsetCenter_ = new Vector3(0, 0, 0); //By default no offset
	}

	RigidBody::RigidBody(Entity* e) : Component( e) {

	}

	RigidBody::RigidBody(Entity* e, ColliderType type, BodyType bType, float mass, int mask, int group, bool isTrigger) : Component(e) {
		type_ = type;
		bType_ = bType;
		mass_ = mass;
		friction_ = 0.3;
		restitution_ = 0.1f;

		isTrigger_ = isTrigger;
		group_ = group;
		mask_ = mask;

		dimensions_ = new Vector3(1, 1, 1); //By default
		offsetCenter_ = new Vector3(0, 0, 0); //By default no offset
	}

	RigidBody::~RigidBody() {
		delete dimensions_; delete offsetCenter_; 
		delete collisionInfo; delete btTransform_;
		delete rbState;

		dimensions_ = nullptr; offsetCenter_ = nullptr; 
		collisionInfo = nullptr; btTransform_ = nullptr;
		rbState = nullptr;
	};

	std::string RigidBody::GetId() {
		return name;
	}

	void RigidBody::setTrigger(bool value) {
		isTrigger = value;
	}

	//In both of this methods 0=x 1=y 2=z
	void RigidBody::setRotConstraints(Vector3 newValue) {
		rotationConstraints[0] = newValue.x;
		rotationConstraints[1] = newValue.y;
		rotationConstraints[2] = newValue.z;

		if (rb != nullptr)
			rb->setAngularFactor(btVector3(rotationConstraints[0], rotationConstraints[1], rotationConstraints[2]));
	}

	void RigidBody::setPosConstraints(Vector3 newValue) {
		positionConstraints[0] = newValue.x;
		positionConstraints[1] = newValue.y;
		positionConstraints[2] = newValue.z;
		if (rb != nullptr)
			rb->setLinearFactor(btVector3(positionConstraints[0], positionConstraints[1], positionConstraints[2]));
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

		btTransform_ = K_Engine::PhysicsManager::GetInstance()->createTransform(transformRf_->getPosition(), 
			*offsetCenter_, transformRf_->getRotation());

		Vector3 scale = transformRf_->getScale();
		btVector3 scale_ = { (btScalar)scale.x, (btScalar)scale.y, (btScalar)scale.z };
		btVector3 dimensions = { (btScalar)dimensions_->x, (btScalar)dimensions_->y, (btScalar)dimensions_->z };
		collisionInfo = new K_Engine::CollisionInfo(this->entity,
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


		rb = world_->addRigidBody(type_, *btTransform_, dimensions, scale_, bType_, mass_, restitution_, friction_, group_, 
			mask_, isTrigger_, collisionInfo);

		rb->setLinearFactor(btVector3(positionConstraints[0], positionConstraints[1], positionConstraints[2]));
		rb->setAngularFactor(btVector3(rotationConstraints[0], rotationConstraints[1], rotationConstraints[2]));
	}

	void RigidBody::init(K_Map* information)
	{
		std::string typ = information->value("Type");

		if (typ == "Static") bType_ = BodyType::BT_STATIC;
		else bType_ = BodyType::BT_DYNAMIC;

		std::string col = information->value("Collider");

		if (col == "Box") type_ = ColliderType::CT_BOX;
		else if (col == "Sphere") type_ = ColliderType::CT_SPHERE;
		else if (col == "Trimesh") type_ = ColliderType::CT_TRIMESH;
		else type_ = ColliderType::CT_HULL;

		if (dimensions_ != nullptr)
			delete dimensions_;
		dimensions_ = information->valueToVector3("Dimensions");

		mass_ = information->valueToNumber("Mass");

		isTrigger = information->valueToBool("isTrigger");
	}

	void RigidBody::update(int frameTime) {
		btVector3 pos = rb->getWorldTransform().getOrigin();
		btScalar y;
		btScalar z;
		btScalar x;
		rb->getWorldTransform().getRotation().getEulerZYX(z, y, x);

		//set new position
		transformRf_->setPosition(pos.x() - offsetCenter_->x, pos.y() - offsetCenter_->y, pos.z() - offsetCenter_->z);
		transformRf_->setRotation(x, y, z);
	}

	void RigidBody::debug() {

	}

	void RigidBody::syncScale() {
		Vector3 scale = transformRf_->getScale();
		btVector3 scale_ = { (btScalar)scale.x, (btScalar)scale.y, (btScalar)scale.z };
		//world_->scaleCollisionShape(rb, scale_);
		btCollisionShape* rbShape = rb->getCollisionShape();
		rbShape->setLocalScaling(scale_);
		world_->getBtWorld()->updateSingleAabb(rb);
	}

	void RigidBody::setDimensions(Vector3 const& toAdd) {
		(*dimensions_) = toAdd;
	}

	void RigidBody::setDimensions(float d) {
		Vector3 toAdd = { d, d, d };
		(*dimensions_) = toAdd;
	}

	void RigidBody::addForce(Vector3 const& value){
		btVector3 force = { (btScalar)value.x,(btScalar)value.y,(btScalar)value.z };
		Vector3 p = transformRf_->getPosition();
		btVector3 pos = { (btScalar)p.x,(btScalar)p.y,(btScalar)p.z };
		rb->applyForce(force, pos);
	}
	
	void RigidBody::addImpulse(Vector3 const& value) {

	}

	void RigidBody::addExplosionForce(Vector3 const& value){

	}

	Vector3 RigidBody::getVelocity()
	{
		btVector3 speed = rb->getLinearVelocity();
		return Vector3((double)speed.x(), (double)speed.y(), (double)speed.z());
	}

	void RigidBody::setOffset(Vector3 const& distance) {
		(*offsetCenter_) = distance;
	}

	void RigidBody::launchEnterCallbacks(void* entity)
	{
		Entity* otherEntity = (Entity*)entity;
		colisionando = true;
		/*std::cout << "Entro\n";*/

		std::vector<Component*> components;

		for (auto c : components) {
			c->onCollisionEnter(otherEntity);
		}
	}

	void RigidBody::launchStayCallbacks(void* entity)
	{
		Entity* otherEntity = (Entity*)entity;
		if (colisionando) {
			/*std::cout << "Estoy\n";*/

		}

		std::vector<Component*> components;

		for (auto c : components) {
			c->onCollisionStay(otherEntity);
		}
	}

	void RigidBody::launchExitCallbacks(void* entity)
	{
		Entity* otherEntity = (Entity*)entity;
		colisionando = false;
		/*std::cout << "Salgo\n";*/

		std::vector<Component*> components;

		for (auto c : components) {
			c->onCollisionExit(otherEntity);
		}

	}
}