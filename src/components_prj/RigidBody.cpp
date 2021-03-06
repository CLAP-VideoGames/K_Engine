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
#include <utils_prj/Math.h>

//CAmbios
#include <input_prj/InputManager.h>
#include <input_prj/K_Engine_Keys.h>

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

	RigidBody::RigidBody(Entity* e) : Component(e) {

	}

	RigidBody::RigidBody(Entity* e, ColliderType type, BodyType bType, float mass, int group, int mask, bool isTrigger) : Component(e) {
		type_ = type;
		bType_ = bType;
		mass_ = mass;
		friction_ = 0.3;
		restitution_ = 0.1f;

		isTrigger_ = isTrigger;
		group_ = group;
		mask_ = mask;

		//std::cout << group << " " << mask << "\n";

		dimensions_ = new Vector3(1, 1, 1); //By default
		offsetCenter_ = new Vector3(0, 0, 0); //By default no offset
	}

	RigidBody::~RigidBody() {
		rb->setUserPointer(nullptr);
		world_->deleteRigidBody(rb);
		delete dimensions_; delete offsetCenter_;
		delete collisionInfo; delete btTransform_;
		delete rbState;
		delete rb;

		dimensions_ = nullptr; offsetCenter_ = nullptr;
		collisionInfo = nullptr; btTransform_ = nullptr;
		rbState = nullptr; rb = nullptr;
	};

	std::string RigidBody::GetId() {
		return name;
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

		isTrigger_ = information->valueToBool("isTrigger");

		mask_ = 1;
		group_ = 1;
		if (information->hasValue("friction"))
			friction_ = information->valueToNumber("friction");

		if (information->hasValue("restitution"))
			restitution_ = information->valueToNumber("restitution");

		if (information->hasValue("group")) {
			std::string groupName = information->value("group");
			groupName[0] = tolower(groupName[0]);
			if (PhysicsManager::GetInstance()->getLayerID(groupName)) {
				PhysicsManager::GetInstance()->addLayer(groupName);
			}
			group_ = PhysicsManager::GetInstance()->getLayerID(groupName);
		}

		if (information->hasValue("mask")) {
			std::vector<std::string> masks = information->valueToVector<std::string>("mask");
			mask_ = 0;
			for (std::string currentMask : masks) {
				mask_ |= PhysicsManager::GetInstance()->getLayerID(currentMask);
			}
		}

		if (information->hasValue("offsetCenter")) {
			if (offsetCenter_ != nullptr)
				delete offsetCenter_;
			if (information->hasValue("offsetCenter"))
				offsetCenter_ = information->valueToVector3("offsetCenter");
		}
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
		rb->applyGravity();
		if (bType_ == BodyType::BT_DYNAMIC)disableDeactivation();
		syncScale();
		syncRotation();
	}


	void RigidBody::update(int frameTime) {
		if (rb != nullptr && bType_ != BodyType::BT_STATIC) {
			btVector3 pos = rb->getWorldTransform().getOrigin();
			btScalar x, y, z;
			rb->getWorldTransform().getRotation().getEulerZYX(z, y, x);

			//set new position
			transformRf_->setPosition(pos.x() - offsetCenter_->x, pos.y() - offsetCenter_->y, pos.z() - offsetCenter_->z);
			transformRf_->updateRotationFromPhysics(x, y, z);

			if (forceToAdd != Vector3(0, 0, 0)) {
				addForce(forceToAdd);
				forceToAdd = Vector3(0, 0, 0);
			}
		}
	}

	void RigidBody::setTrigger(bool value) {
		isTrigger_ = value;
	}

	//In both of this methods 0=x 1=y 2=z
	void RigidBody::setRotConstraints(Vector3 newValue) {

		rotationConstraints[0] = newValue.y;
		rotationConstraints[1] = newValue.z;
		rotationConstraints[2] = newValue.x;

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

	void RigidBody::syncScale() {
		Vector3 scale = transformRf_->getScale();
		btVector3 scale_ = { (btScalar)scale.x, (btScalar)scale.y, (btScalar)scale.z };
		//world_->scaleCollisionShape(rb, scale_);
		btCollisionShape* rbShape = rb->getCollisionShape();
		rbShape->setLocalScaling(scale_);
		world_->getBtWorld()->updateSingleAabb(rb);
	}

	void RigidBody::syncRotation() {
		if (!transformRf_)
			transformRf_ = entity->getComponent<Transform>();

		Vector3 rotation = transformRf_->getRotation();
		btVector3 rot = { (btScalar)btRadians(rotation.x), (btScalar)btRadians(rotation.y), (btScalar)btRadians(rotation.z) };
		rb->getWorldTransform().setRotation(btQuaternion(rot.y(), rot.x(), rot.z()));
	}

	void RigidBody::setDimensions(Vector3 const& toAdd) {
		(*dimensions_) = toAdd;
	}

	void RigidBody::setDimensions(float d) {
		Vector3 toAdd = { d, d, d };
		(*dimensions_) = toAdd;
	}

	void RigidBody::disableDeactivation() {
		rb->setActivationState(DISABLE_DEACTIVATION);
	}

	void RigidBody::addForce(Vector3 const& value) {
		if (transformRf_ != nullptr) {
			btVector3 force = { (btScalar)value.x,(btScalar)value.y,(btScalar)value.z };
			Vector3 p = transformRf_->getPosition();
			btVector3 pos = { (btScalar)p.x,(btScalar)p.y,(btScalar)p.z };
			rb->applyForce(force, pos);
		}
		else forceToAdd += value;
	}

	void RigidBody::addForceImpulse(Vector3 const& value) {
		btVector3 force = { (btScalar)value.x,(btScalar)value.y,(btScalar)value.z };
		rb->applyCentralImpulse(force);
	}

	void RigidBody::setVelocity(Vector3 const& value)
	{
		rb->setLinearVelocity(btVector3((btScalar)value.x, (btScalar)value.y, (btScalar)value.z));
	}

	void RigidBody::translate(Vector3 const& value)
	{
		rb->translate({(btScalar)value.x,(btScalar)value.y,(btScalar)value.z });
	}

	void RigidBody::setRotation(Vector3 const& value)
	{
		rb->getWorldTransform().setRotation(btQuaternion(value.z, value.y, value.x));
	}

	Vector3 RigidBody::getVelocity()
	{
		btVector3 speed = rb->getLinearVelocity();
		return Vector3((double)speed.x(), (double)speed.y(), (double)speed.z());
	}

	Vector3 RigidBody::getRotationBody() {
		btScalar y;
		btScalar z;
		btScalar x;
		rb->getWorldTransform().getRotation().getEulerZYX(x, z, y);

		return { Math::toEuler((float)x),Math::toEuler((float)y), Math::toEuler((float)z) };
	}

	float RigidBody::getMass() const {
		return mass_;
	}

	void RigidBody::setOffset(Vector3 const& distance) {
		(*offsetCenter_) = distance;
	}

	void RigidBody::launchEnterCallbacks(void* ent)
	{
		Entity* otherEntity = (Entity*)ent;
		colisionando = true;

		std::unordered_map<std::string, Component*>* components = entity->getComponents();

		for (auto c : *components) {
			c.second->onCollisionEnter(otherEntity);
		}
	}

	void RigidBody::launchStayCallbacks(void* ent)
	{
		Entity* otherEntity = (Entity*)ent;

		std::unordered_map<std::string, Component*>* components = entity->getComponents();

		for (auto c : *components) {
			c.second->onCollisionStay(otherEntity);
		}
	}

	void RigidBody::launchExitCallbacks(void* ent)
	{
		Entity* otherEntity = (Entity*)ent;
		colisionando = false;
		/*std::cout << "Salgo\n";*/

		std::unordered_map<std::string, Component*>* components = entity->getComponents();

		for (auto c : *components) {
			c.second->onCollisionExit(otherEntity);
		}

	}
}