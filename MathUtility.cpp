#include"MathUtility.h"
#include<random>
using namespace std;
using namespace MathUtility;

float Random(float min, float max) {
	float min_, max_;
	if (min > max) {
		min_ = max;
		max_ = min;
	}
	else {
		min_ = min;
		max_ = max;

	}

	//—”
	random_device seed_gem;
	mt19937_64 engine(seed_gem());
	uniform_real_distribution<float> rotDist(min_, max_);

	return rotDist(engine);
}

double EaseOut(double x) {
	return sin(x * PI / 2);
}