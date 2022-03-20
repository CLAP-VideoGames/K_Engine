#ifndef CUSTOMVECTOR_H
#define CUSTOMVECTOR_H

struct KVector3
{
public:
	double x, y, z;

	KVector3() : x(0), y(0), z(0) {};
	KVector3(double _x, double _y, double _z) : x(_x), y(_y), z(_z) {};

	~KVector3() {};

	KVector3 operator+(KVector3 const& other);
	KVector3 operator-(KVector3 const& other);
	KVector3 operator*(KVector3 const& other);
	KVector3 operator/(KVector3 const& other);
	void operator+=(KVector3 const& other);
	void operator-=(KVector3 const& other);
	double& operator[](int);
	float getMagnitude();
	KVector3 normalized();
	void normalize();
};
#endif // CUSTOMVECTOR_H