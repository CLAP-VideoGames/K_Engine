#include "Transform.h"
#include <utils_prj/CustomVector3.h>

std::string Transform::name = "Transform";

Transform::Transform(Entity* e) : Component("Transform", e)
{ 
	position_ = new CustomVector3{ 0, 0, 0 };
	rotation_ = new CustomVector3{ 0, 0, 0 };
	scale_ = new CustomVector3{ 1, 1, 1 };
}

Transform::~Transform() {
	delete position_; position_ = nullptr;
	delete rotation_; rotation_ = nullptr;
	delete scale_; scale_ = nullptr;
}

std::string Transform::GetId()
{
	return name;
}

void Transform::translate(float x, float y, float z)
{
	CustomVector3 toAdd = { x, y, z };
	(*position_) += toAdd;
}

void Transform::rotate(float x, float y, float z) {
	CustomVector3 toAdd = { x, y, z };
	(*rotation_) += toAdd;
}

void Transform::scale(float x, float y, float z){
	CustomVector3 toAdd = { x, y, z };
	(*scale_) += toAdd;
}

void Transform::setPosition(float x, float y, float z) {
	CustomVector3 toAdd = { x, y, z };
	(*position_) = toAdd;
}

void Transform::setRotation(float x, float y, float z) {
	CustomVector3 toAdd = { x, y, z };
	(*rotation_) = toAdd;
}

void Transform::setScale(float x, float y, float z)
{
	CustomVector3 toAdd = { x, y, z };
	(*scale_) = toAdd;
}

CustomVector3 Transform::getPosition()
{
	return *position_;
}

CustomVector3  Transform::getRotation()
{
	return *rotation_;
}

CustomVector3  Transform::getScale()
{
	return *scale_;
}

void Transform::debug()
{
	setScale(0.2, 0.2, 0.2);
}
