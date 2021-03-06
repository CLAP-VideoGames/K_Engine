#include "Transform.h"

#include <components_prj/RigidBody.h>
#include <components_prj/MeshRenderer.h>

#include <ecs_prj/Entity.h>

#include <utils_prj/Vector3.h>
#include <utils_prj/checkML.h>
#include <utils_prj/K_Map.h>

#include <iostream>

namespace K_Engine {
	std::string Transform::name = "Transform";

	std::string Transform::GetId() {
		return name;
	}

	Transform::Transform(): Component() {
	}

	Transform::Transform(Entity* e) : Component(e){
		position_ = new Vector3{ 0, 0, 0 };
		rotation_ = new Vector3{ 0, 0, 0 };
		scale_ = new Vector3{ 1, 1, 1 };
	}

	Transform::~Transform() {
		delete position_; position_ = nullptr;
		delete rotation_; rotation_ = nullptr;
		delete scale_; scale_ = nullptr;
	}

	void Transform::init(K_Map* information)
	{
		position_ = information->valueToVector3("position");
		rotation_ = information->valueToVector3("rotation");
		scale_ = information->valueToVector3("scale");
	}

	void Transform::translate(float x, float y, float z)
	{
		Vector3 toAdd = { x, y, z };
		std::vector<Entity*> children = entity->getChildren();

		for (auto c : children) {

			//Translate childre
			Transform* childT = c->getComponent<Transform>();

			childT->translate(x, y, z);
		}

		(*position_) += toAdd;
	}

	void Transform::rotate(float x, float y, float z) {
		Vector3 toAdd = { x, y, z };
		(*rotation_) += toAdd;

		std::cout << (*rotation_).x << " " << (*rotation_).y << " " << (*rotation_).z << "\n";

		RigidBody* rb = entity->getComponent<RigidBody>();
		if (rb) {
			rb->syncRotation();
		}

	}

	void Transform::scale(float x, float y, float z) {
		Vector3 toAdd = { x, y, z };
		(*scale_) += toAdd;


		RigidBody* rb = entity->getComponent<RigidBody>();
		if (rb) {
			rb->syncScale();
		}

		MeshRenderer* mR = entity->getComponent<MeshRenderer>();
		if (mR) {
			mR->syncScale();
		}

		std::vector<Entity*> children = entity->getChildren();

		for (auto c : children) {
			c->getComponent<Transform>()->scale(x, y, z);
		}

	}

	void Transform::setPosition(float x, float y, float z) {
		Vector3 toSet = { x, y, z };

		std::vector<Entity*> children = entity->getChildren();

		for (auto c : children) {

			//Data for the calculation
			Transform* childT = c->getComponent<Transform>();

			Vector3 childPos = childT->getPosition();

			Vector3 oldParentPos = getPosition();

			Vector3 toSetChild = toSet;

			//Get the diference between new pos and oldPos
			toSetChild.x = oldParentPos.x;
			toSetChild.y = oldParentPos.y;
			toSetChild.z = oldParentPos.z;

			//Set its new position with the parent as (0,0,0)
			childT->setPosition((childPos.x + toSetChild.x), (childPos.y + toSetChild.y), (childPos.z + toSetChild.z));
		}

		(*position_) = toSet;
	}

	void Transform::setRotation(float x, float y, float z) {
		Vector3 toAdd = { x, y, z };
		(*rotation_) = toAdd;

		RigidBody* rb = entity->getComponent<RigidBody>();
		if (rb) {
			rb->syncRotation();
		}
	}

	void Transform::updateRotationFromPhysics(float x, float y, float z){
		Vector3 toAdd = { x, y, z };
		(*rotation_) = toAdd;
	}

	void Transform::setScale(float x, float y, float z) {
		Vector3 toSet = { x, y, z };
		(*scale_) = toSet;

		std::vector<Entity*> children = entity->getChildren();

		for (auto c : children) {

			//Data for the calculation
			Transform* childT = c->getComponent<Transform>();

			Vector3 childScale = childT->getScale();

			Vector3 oldParentScale = getScale();

			Vector3 toSetChild = toSet;

			//Get the diference between new pos and oldPos
			toSetChild.x -= oldParentScale.x;
			toSetChild.y -= oldParentScale.y;
			toSetChild.z -= oldParentScale.z;

			//Set its new position with the parent as (0,0,0)
			childT->setScale((childScale.x + toSetChild.x), (childScale.y + toSetChild.y), (childScale.z + toSetChild.z));
		}

		RigidBody* rb = entity->getComponent<RigidBody>();
		if (rb) {
			rb->syncScale();
		}

		MeshRenderer* mR = entity->getComponent<MeshRenderer>();
		if (mR) {
			mR->syncScale();
		}
	}

	void Transform::setScale(float n) {
		Vector3 toSet = { n, n, n };
		(*scale_) = toSet;
		std::vector<Entity*> children = entity->getChildren();

		for (auto c : children) {

			//Data for the calculation
			Transform* childT = c->getComponent<Transform>();

			Vector3 childScale = childT->getScale();

			Vector3 oldParentScale = getScale();

			Vector3 toSetChild = toSet;

			//Get the diference between new pos and oldPos
			toSetChild.x -= oldParentScale.x;
			toSetChild.y -= oldParentScale.y;
			toSetChild.z -= oldParentScale.z;

			//Set its new position with the parent as (0,0,0)
			childT->setScale((childScale.x + toSetChild.x), (childScale.y + toSetChild.y), (childScale.z + toSetChild.z));
		}

		RigidBody* rb = entity->getComponent<RigidBody>();
		if (rb) {
			rb->syncScale();
		}

		MeshRenderer* mR = entity->getComponent<MeshRenderer>();
		if (mR) {
			mR->syncScale();
		}
	}

	Vector3 Transform::getPosition() const {
		return *position_;
	}

	Vector3  Transform::getRotation()const {
		return *rotation_;
	}

	Vector3  Transform::getScale() const {
		return *scale_;
	}

	//Vector3 Transform::getDimensions() const {
	//	return *dimensions_;
	//}

	void Transform::debug(){
		test = true;
		time = timer;
		times = 0;
		//setScale(0.2, 0.2, 0.2);
	}

	void Transform::update(int frameTime) {
		//printf("world girar object = %f,%f,%f\n", float(rotation_->x), float(rotation_->y), float(rotation_->z));
		//printf("world pos object  = %f,%f,%f\n",  float(position_->x), float(position_->y), float(position_->z));
		//printf("________\n");
	}
}