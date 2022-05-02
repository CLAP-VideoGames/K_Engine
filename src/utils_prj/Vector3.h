#pragma once
#ifndef VECTOR_H
#define VECTOR_H

namespace K_Engine {
	struct  __declspec(dllexport) Vector3 {
	public:
		double x, y, z;

		Vector3();
		Vector3(double _x, double _y, double _z);
		~Vector3();

		Vector3 operator+(Vector3 const& other);
		Vector3 operator-(Vector3 const& other);
		Vector3 operator*(Vector3 const& other);
		Vector3 operator/(Vector3 const& other);
		bool operator!=(Vector3 const& other);
		bool operator==(Vector3 const& other);
		void operator+=(Vector3 const& other);
		void operator-=(Vector3 const& other);
		double& operator[](int);

		/// <summary>
		/// Size of the vector
		/// </summary>
		/// <returns></returns>
		float getMagnitude();

		/// <summary>
		/// Returns a vector copy normalized
		/// </summary>
		Vector3 normalized();

		/// <summary>
		/// Normalize the current vector
		/// </summary>
		void normalize();
	};
}
#endif //VECTOR_H