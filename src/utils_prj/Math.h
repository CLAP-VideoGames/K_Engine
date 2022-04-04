#pragma once
#ifndef MATH_H
#define MATH_H


namespace K_Engine {
	class Vector3;
	namespace Math {
		const double PI = 3.1415926;
		/// <summary>
		/// Initialize a random seed
		/// </summary>
		void initSeed();

		/// <summary>
		/// Converts an angle to radians
		/// </summary>
		/// <param name="angle">angle to be converted</param>
		/// <returns>radians value</returns>
		float toRadians(float angle);
		/// <summary>
		/// Returns a random decimal value between min a max
		/// </summary>
		/// <param name="min">min value included</param>
		/// <param name="max">max value included</param>
		float random_double(double min, double max);
		/// <summary>
		/// Returns a random integer value between min a max
		/// </summary>
		/// <param name="min">min value included</param>
		/// <param name="max">max value included</param>
		int random_int(int min, int max);

		/// <summary>
		/// Returns a random vector between min a max
		/// </summary>
		/// <param name="min">min value included</param>
		/// <param name="max">max value included</param>
		Vector3 random_vector(Vector3 const& min, Vector3 const& max);

		/// <summary>
		/// Interpolates a to b given a t factor
		/// </summary>
		/// <param name="a">from</param>
		/// <param name="b">to</param>
		/// <param name="t">factor between [0, 1] </param>
		float lerpPrecise(float a, float b, float t);

		float squareRoot(float n);

		float powOf(float base, float power);
	}
}
#endif //MATH_H