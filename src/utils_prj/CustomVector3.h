#ifndef CUSTOMVECTOR_H
#define CUSTOMVECTOR_H

struct CustomVector3
{
public:
	double x, y, z;

	CustomVector3() : x(0), y(0), z(0) {};
	CustomVector3(double _x, double _y, double _z) : x(_x), y(_y), z(_z) {};

	~CustomVector3() {};

	CustomVector3 operator+(CustomVector3 const& other);
	CustomVector3 operator-(CustomVector3 const& other);
	CustomVector3 operator*(CustomVector3 const& other);
	CustomVector3 operator/(CustomVector3 const& other);
	void operator+=(CustomVector3 const& other);
	void operator-=(CustomVector3 const& other);
	double& operator[](int);
	float getMagnitude();
	CustomVector3 normalized();
	void normalize();
};
#endif // CUSTOMVECTOR_H