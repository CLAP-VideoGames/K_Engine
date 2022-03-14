#ifndef CUSTOMVECTOR_H
#define CUSTOMVECTOR_H

class CustomVector3
{
public:
	double x, y, z;

	CustomVector3() : x(0), y(0), z(0) {};
	CustomVector3(double _x, double _y, double _z) : x(_x), y(_y), z(_z) {};

	~CustomVector3() {};

	CustomVector3 operator+(CustomVector3 other);
	CustomVector3 operator-(CustomVector3 other);
	CustomVector3 operator*(CustomVector3 other);
	CustomVector3 operator/(CustomVector3 other);
	void operator+=(CustomVector3 other);
	void operator-=(CustomVector3 other);
	float getMagnitude();
	CustomVector3 normalized();
	void normalize();
};
#endif // CUSTOMVECTOR_H