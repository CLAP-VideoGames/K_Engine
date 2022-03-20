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
class KVector3;

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
	KVector3 getPosition();
	KVector3 getRotation();
	KVector3 getScale();

	virtual void debug();
	virtual void update();

private:
	static std::string name;
	
	//Arrays initialized to default values
	// x y z axis, in that order of our 3 main information arrays
	KVector3* position_;
	KVector3* rotation_;
	KVector3* scale_;
}; 
#endif // TRANSFORM_H