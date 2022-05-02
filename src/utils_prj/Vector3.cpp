#include "Vector3.h"

#include <cassert> 
#include "Math.h"

namespace K_Engine {
	Vector3::Vector3() : x(0), y(0), z(0) {};
	Vector3::Vector3(double _x, double _y, double _z) : x(_x), y(_y), z(_z) {};
	Vector3::~Vector3() = default;

	Vector3 Vector3::operator+(Vector3 const& other)
	{
		return Vector3(this->x + other.x, this->y + other.y, this->z + other.z);
	}

	Vector3 Vector3::operator-(Vector3 const& other)
	{
		return Vector3(this->x - other.x, this->y - other.y, this->z - other.z);
	}

	Vector3 Vector3::operator*(Vector3 const& other)
	{
		return Vector3(this->x * other.x, this->y * other.y, this->z * other.z);
	}

	Vector3 Vector3::operator/(Vector3 const& other)
	{
		return Vector3(this->x / other.x, this->y / other.y, this->z / other.z);
	}

	bool Vector3::operator!=(Vector3 const& other)
	{
		return !(*this == other);
	}

	bool Vector3::operator==(Vector3 const& other)
	{
		return x == other.x && y == other.y && z == other.z;
	}

	void Vector3::operator+=(Vector3 const& other)
	{
		this->x += other.x;
		this->y += other.y;
		this->z += other.z;
	}

	void Vector3::operator-=(Vector3 const& other)
	{
		this->x -= other.x;
		this->y -= other.y;
		this->z -= other.z;
	}

	double& Vector3::operator[](int index) {

		assert(index < 3, "Index out of bounds.");

		switch (index) {
		case 0:
			return x;
		case 1:
			return y;
		case 2:
			return z;
		}
	}

	float Vector3::getMagnitude()
	{
		return Math::squareRoot(Math::powOf(x, 2) + Math::powOf(y, 2) + Math::powOf(z, 2));
	}

	Vector3 Vector3::normalized()
	{
		float magnitude = getMagnitude();
		return Vector3(x / magnitude, y / magnitude, z / magnitude);
	}

	void Vector3::normalize()
	{
		float magnitude = getMagnitude();
		x /= magnitude;
		y /= magnitude;
		z /= magnitude;
	}
}