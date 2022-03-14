#include "EngineMath.h"
#include <math.h>
#include <time.h>
#include <stdlib.h>
#include "CustomVector3.h"

void Math::initSeed(){
	srand((unsigned)time(NULL));
}

float Math::toRadians(float angle){
	return angle * PI / 180.0;
}

float Math::random_double(double min, double max){
	return (max - min) * ((double) rand() / RAND_MAX) + min;
}

int Math::random_int(int min, int max){
	return rand() % max + min;
}

CustomVector3 Math::random_vector(CustomVector3 const& min, CustomVector3 const& max) {
	return CustomVector3(random_double(min.x, max.x), random_double(min.y, max.y), random_double(min.z, max.z));
}

float Math::lerpPrecise(float a, float b, float t){
	return a * (1 - t) + b * t;
}



