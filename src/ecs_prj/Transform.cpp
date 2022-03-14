#include "Transform.h"

std::string Transform::name = "Transform";

Transform::Transform(Entity* e) : Component("Transform", e)
{ 
	position_ = { 0, 0, 0 };
	rotation_ = { 0, 0, 0 };
	scale_ = { 1, 1, 1 };
}

Transform::~Transform() = default;

std::string Transform::GetId()
{
	return name;
}

void Transform::translate(float x, float y, float z)
{
	float toAdd[3] = { x, y, z };

	for (int i = 0; i < 3; i++) {
		position_[i] += toAdd[i];
	}
}

void Transform::rotate(float x, float y, float z)
{
	float toAdd[3] = { x, y, z };

	for (int i = 0; i < 3; i++)
		rotation_[i] += toAdd[i];
}

void Transform::scale(float x, float y, float z)
{
	float toAdd[3] = { x, y, z };

	for (int i = 0; i < 3; i++)
		scale_[i] += toAdd[i];
}

void Transform::setPosition(float x, float y, float z)
{
	float toAdd[3] = { x, y, z };

	for (int i = 0; i < 3; i++) 
		position_[i] = toAdd[i];
}

void Transform::setRotation(float x, float y, float z)
{
	float toAdd[3] = { x, y, z };

	for (int i = 0; i < 3; i++) 
		rotation_[i] = toAdd[i];
}

void Transform::setScale(float x, float y, float z)
{
	float toAdd[3] = { x, y, z };

	for (int i = 0; i < 3; i++)
		scale_[i] = toAdd[i];
}

std::vector<float> Transform::getPosition()
{
	return position_;
}

std::vector<float>  Transform::getRotation()
{
	return rotation_;
}

std::vector<float>  Transform::getScale()
{
	return scale_;
}

void Transform::debug()
{
	setScale(0.2, 0.2, 0.2);
}
