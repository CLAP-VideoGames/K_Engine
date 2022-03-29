#include "Math.h"

#include <time.h>
#include <stdlib.h>

#include <utils_prj/Vector3.h>

namespace K_Engine {
	void Math::initSeed() {
		srand((unsigned)time(NULL));
	}

	float Math::toRadians(float angle) {
		return angle * PI / 180.0;
	}

	float Math::random_double(double min, double max) {
		return (max - min) * ((double)rand() / RAND_MAX) + min;
	}

	int Math::random_int(int min, int max) {
		return rand() % max + min;
	}

	Vector3 Math::random_vector(Vector3 const& min, Vector3 const& max) {
		return Vector3(random_double(min.x, max.x), random_double(min.y, max.y), random_double(min.z, max.z));
	}

	float Math::lerpPrecise(float a, float b, float t) {
		return a * (1 - t) + b * t;
	}
}