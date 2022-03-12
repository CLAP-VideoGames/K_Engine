#pragma once
#include "Component.h"
#include <vector>

/*
* The Transform component is used to store information about our entity
* This component is the place from where rigidBody and meshRenderer take the information
* To use physics and to render our entities
*/
class Transform : public Component
{
public:
	Transform();
	~Transform();

	static std::string GetId();

	//These 3 methods add the the amount that we introduce in them to our current arrays
	void translate(float x, float y, float z);
	void rotate(float x, float y, float z);
	void Scale(float x, float y, float z);

	//These 3 methods set our arrays to the parameter we introduce in them
	void setPosition(float x, float y, float z);
	void setRotation(float x, float y, float z);
	void setScale(float x, float y, float z);

	//These 3 methods set our arrays to the parameter we introduce in them
	float* getPosition(float x, float y, float z);
	float* getRotation(float x, float y, float z);
	float* getScale(float x, float y, float z);

private:
	static std::string name;
	
	//Arrays initialized to default values
	// x y z axis, in that order of our 3 main information arrays
	float position[3] = { 0, 0, 0 };
	float rotation[3] = { 0, 0, 0 };
	float scale[3] = { 1, 1, 1 };
};