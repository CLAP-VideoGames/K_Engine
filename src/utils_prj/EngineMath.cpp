#include "EngineMath.h"
#include <math.h>
#include <time.h>
#include <stdlib.h>

void Math::initSeed(){
	srand((unsigned)time(NULL));
}

float Math::toRadians(float const& angle){
	return angle * PI / 180.0;
}

float Math::random_float(float min, float max){
	return (max - min) * ((float) rand() / RAND_MAX) + min;
}

int Math::random_int(int min, int max){
	return rand() % max + min;
}

float Math::lerpPrecise(float a, float b, float t){
	return a * (1 - t) + b * t;
}



