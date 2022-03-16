#include "CustomVector3.h"
#include <cassert> 
#include <math.h>

CustomVector3 CustomVector3::operator+(CustomVector3 const& other)
{
	return CustomVector3(this->x + other.x, this->y + other.y, this->z + other.z);
}

CustomVector3 CustomVector3::operator-(CustomVector3 const&  other)
{
	return CustomVector3(this->x - other.x, this->y - other.y, this->z - other.z);
}

CustomVector3 CustomVector3::operator*(CustomVector3 const&  other)
{
	return CustomVector3(this->x * other.x, this->y * other.y, this->z * other.z);
}

CustomVector3 CustomVector3::operator/(CustomVector3 const&  other)
{
	return CustomVector3(this->x / other.x, this->y / other.y, this->z / other.z);
}

void CustomVector3::operator+=(CustomVector3 const&  other)
{
	this->x += other.x;
	this->y += other.y;
	this->z += other.z;
}

void CustomVector3::operator-=(CustomVector3 const&  other)
{
	this->x -= other.x;
	this->y -= other.y;
	this->z -= other.z;
}

double& CustomVector3::operator[](int index){

	assert(index< 3, "Index out of bounds.");

	switch (index){
		case 0:
			return x;
		case 1:
			return y;
		case 2:
			return z;
	}
}

float CustomVector3::getMagnitude()
{
	return sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2));
}

CustomVector3 CustomVector3::normalized()
{
	float magnitude = getMagnitude();
	return CustomVector3(x / magnitude, y / magnitude, z / magnitude);
}

void CustomVector3::normalize()
{
	float magnitude = getMagnitude();
	x /= magnitude;
	y /= magnitude;
	z /= magnitude;
}
