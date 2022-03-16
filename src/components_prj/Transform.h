#pragma once
#ifndef TRANSFORM_H
#define TRANSFORM_H

#include <vector>

#include <ecs_prj/Component.h>

/*
* The Transform component is used to store information about our entity
* This component is the place from where rigidBody and meshRenderer take the information
* To use physics and to render our entities
*/
class CustomVector3;

class Transform : public Component
{
public:
	Transform(Entity* e);
	~Transform();

	static std::string GetId();

	//These 3 methods add the the amount that we introduce in them to our current arrays
	void translate(float x, float y, float z);
	void rotate(float x, float y, float z);
	void scale(float x, float y, float z);

	//These 3 methods set our arrays to the parameter we introduce in them
	void setPosition(float x, float y, float z);
	void setRotation(float x, float y, float z);
	void setScale(float x, float y, float z);
	void setScale(float n);

	//These 3 methods set our arrays to the parameter we introduce in them
	CustomVector3 getPosition();
	CustomVector3 getRotation();
	CustomVector3 getScale();

	virtual void debug();

private:
	static std::string name;
	
	//Arrays initialized to default values
	// x y z axis, in that order of our 3 main information arrays
	CustomVector3* position_;
	CustomVector3* rotation_;
	CustomVector3* scale_;
}; 
#endif // TRANSFORM_H