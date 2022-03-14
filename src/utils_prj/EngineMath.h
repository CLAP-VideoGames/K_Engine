#pragma once
namespace Math {
	const double PI = 3.14159265;

	static void initSeed();

	static float toRadians(float const& angle);

	static float random_float(float min, float max);

	static int random_int(int min, int max);

	static float lerpPrecise(float a, float b, float t);
}

