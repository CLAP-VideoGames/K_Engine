#include "Transform.h"

std::string Transform::name = "Transform";

Transform::Transform() : Component("Transform", nullptr) { }

Transform::Transform(Entity* e) : Component("Transform", e) { }

Transform::~Transform() { }

std::string Transform::GetId()
{
	return name;
}

void Transform::translate(float x, float y, float z)
{
	float toAdd[3] = { x, y, z };

	for (int i = 0; i < 3; i++) {
		position[i] += toAdd[i];
	}
}

void Transform::rotate(float x, float y, float z)
{
	float toAdd[3] = { x, y, z };

	for (int i = 0; i < 3; i++)
		rotation[i] += toAdd[i];
}

void Transform::Scale(float x, float y, float z)
{
	float toAdd[3] = { x, y, z };

	for (int i = 0; i < 3; i++)
		scale[i] += toAdd[i];
}

void Transform::setPosition(float x, float y, float z)
{
	float toAdd[3] = { x, y, z };

	for (int i = 0; i < 3; i++) 
		position[i] = toAdd[i];
}

void Transform::setRotation(float x, float y, float z)
{
	float toAdd[3] = { x, y, z };

	for (int i = 0; i < 3; i++) 
		rotation[i] = toAdd[i];
}

void Transform::setScale(float x, float y, float z)
{
	float toAdd[3] = { x, y, z };

	for (int i = 0; i < 3; i++)
		scale[i] = toAdd[i];
}

float* Transform::getPosition()
{
	return position;
}

float* Transform::getRotation()
{
	return rotation;
}

float* Transform::getScale()
{
	return scale;
}
