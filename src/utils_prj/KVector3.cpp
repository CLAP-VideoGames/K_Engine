#include "KVector3.h"

#include <cassert> 
#include <math.h>

namespace K_Engine {
	KVector3::KVector3() : x(0), y(0), z(0) {};
	KVector3::KVector3(double _x, double _y, double _z) : x(_x), y(_y), z(_z) {};
	KVector3::~KVector3() = default;

	KVector3 KVector3::operator+(KVector3 const& other)
	{
		return KVector3(this->x + other.x, this->y + other.y, this->z + other.z);
	}

	KVector3 KVector3::operator-(KVector3 const& other)
	{
		return KVector3(this->x - other.x, this->y - other.y, this->z - other.z);
	}

	KVector3 KVector3::operator*(KVector3 const& other)
	{
		return KVector3(this->x * other.x, this->y * other.y, this->z * other.z);
	}

	KVector3 KVector3::operator/(KVector3 const& other)
	{
		return KVector3(this->x / other.x, this->y / other.y, this->z / other.z);
	}

	void KVector3::operator+=(KVector3 const& other)
	{
		this->x += other.x;
		this->y += other.y;
		this->z += other.z;
	}

	void KVector3::operator-=(KVector3 const& other)
	{
		this->x -= other.x;
		this->y -= other.y;
		this->z -= other.z;
	}

	double& KVector3::operator[](int index) {

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

	float KVector3::getMagnitude()
	{
		return sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2));
	}

	KVector3 KVector3::normalized()
	{
		float magnitude = getMagnitude();
		return KVector3(x / magnitude, y / magnitude, z / magnitude);
	}

	void KVector3::normalize()
	{
		float magnitude = getMagnitude();
		x /= magnitude;
		y /= magnitude;
		z /= magnitude;
	}
}