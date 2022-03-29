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
		static void initSeed();

		/// <summary>
		/// Converts an angle to radians
		/// </summary>
		/// <param name="angle">angle to be converted</param>
		/// <returns>radians value</returns>
		static float toRadians(float angle);
		/// <summary>
		/// Returns a random decimal value between min a max
		/// </summary>
		/// <param name="min">min value included</param>
		/// <param name="max">max value included</param>
		static float random_double(double min, double max);
		/// <summary>
		/// Returns a random integer value between min a max
		/// </summary>
		/// <param name="min">min value included</param>
		/// <param name="max">max value included</param>
		static int random_int(int min, int max);

		/// <summary>
		/// Returns a random vector between min a max
		/// </summary>
		/// <param name="min">min value included</param>
		/// <param name="max">max value included</param>
		static Vector3 random_vector(Vector3 const& min, Vector3 const& max);

		/// <summary>
		/// Interpolates a to b given a t factor
		/// </summary>
		/// <param name="a">from</param>
		/// <param name="b">to</param>
		/// <param name="t">factor between [0, 1] </param>
		static float lerpPrecise(float a, float b, float t);
	}
}
#endif //MATH_H