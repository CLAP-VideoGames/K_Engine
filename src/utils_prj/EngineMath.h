class CustomVector3;

namespace Math {
	const double PI = 3.1415926;

	static void initSeed();
	static float toRadians(float angle);
	static float random_double(double min, double max);
	static int random_int(int min, int max);
	static CustomVector3 random_vector(CustomVector3 const& min, CustomVector3 const& max);
	static float lerpPrecise(float a, float b, float t);
}