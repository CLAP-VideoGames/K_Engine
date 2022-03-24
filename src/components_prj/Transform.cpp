#include "Transform.h"
#include "RigidBody.h"
#include "MeshRenderer.h"
#include <ecs_prj/Entity.h>
#include <utils_prj/KVector3.h>

std::string Transform::name = "Transform";

Transform::Transform(Entity* e) : Component("Transform", e)
{ 
	position_ = new KVector3{ 0, 0, 0 };
	rotation_ = new KVector3{ 0, 0, 0 };
	scale_ = new KVector3{ 1, 1, 1 };
	dimensions_ = new KVector3{ 1, 1, 1 };
}

Transform::~Transform() {
	delete position_; position_ = nullptr;
	delete rotation_; rotation_ = nullptr;
	delete scale_; scale_ = nullptr;
	delete dimensions_; dimensions_ = nullptr;
}

std::string Transform::GetId()
{
	return name;
}

void Transform::translate(float x, float y, float z)
{
	KVector3 toAdd = { x, y, z };
	(*position_) += toAdd;
}

void Transform::rotate(float x, float y, float z) {
	KVector3 toAdd = { x, y, z };
	(*rotation_) += toAdd;
}

void Transform::scale(float x, float y, float z){
	KVector3 toAdd = { x, y, z };
	(*scale_) += toAdd;

	RigidBody* rb = entity->getComponent<RigidBody>();
	if (rb) {
		rb->syncScale();
	}

	MeshRenderer* mR = entity->getComponent<MeshRenderer>();
	if (mR) {
		mR->syncScale();
	}

}

void Transform::setPosition(float x, float y, float z) {
	KVector3 toAdd = { x, y, z };
	(*position_) = toAdd;
}

void Transform::setDimensions(float x, float y, float z){
	KVector3 toAdd = { x, y, z };
	(*dimensions_) = toAdd;
}

void Transform::setDimensions(float d){
	KVector3 toAdd = { d, d, d };
	(*dimensions_) = toAdd;
}

void Transform::setRotation(float x, float y, float z) {
	KVector3 toAdd = { x, y, z };
	(*rotation_) = toAdd;
}

void Transform::setScale(float x, float y, float z){
	KVector3 toAdd = { x, y, z };
	(*scale_) = toAdd;
}

void Transform::setScale(float n){
	KVector3 toAdd = { n, n, n };
	(*scale_) = toAdd;
}

KVector3 Transform::getPosition() const {
	return *position_;
}

KVector3  Transform::getRotation()const {
	return *rotation_;
}

KVector3  Transform::getScale() const {
	return *scale_;
}

KVector3 Transform::getDimensions() const {
	return *dimensions_;
}

void Transform::debug()
{
	setScale(0.2, 0.2, 0.2);
}

void Transform::update(){
	//printf("world girar object = %f,%f,%f\n", float(rotation_->x), float(rotation_->y), float(rotation_->z));
	//printf("world pos object  = %f,%f,%f\n",  float(position_->x), float(position_->y), float(position_->z));
	//printf("________\n");
}
