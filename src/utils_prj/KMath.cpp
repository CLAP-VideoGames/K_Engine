#include "KMath.h"

#include <time.h>
#include <stdlib.h>

#include <utils_prj/KVector3.h>

namespace K_Engine {
	void KMath::initSeed() {
		srand((unsigned)time(NULL));
	}

	float KMath::toRadians(float angle) {
		return angle * PI / 180.0;
	}

	float KMath::random_double(double min, double max) {
		return (max - min) * ((double)rand() / RAND_MAX) + min;
	}

	int KMath::random_int(int min, int max) {
		return rand() % max + min;
	}

	KVector3 KMath::random_vector(KVector3 const& min, KVector3 const& max) {
		return KVector3(random_double(min.x, max.x), random_double(min.y, max.y), random_double(min.z, max.z));
	}

	float KMath::lerpPrecise(float a, float b, float t) {
		return a * (1 - t) + b * t;
	}
}