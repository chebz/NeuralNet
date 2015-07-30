#include "Utils.h"

Utils::Utils() : mRandomSeeded(false) {
	srand(static_cast <unsigned> (time(0)));
}

double Utils::random01() const {
	return static_cast<double>(rand()) / static_cast<double>(RAND_MAX);
}

int Utils::randomRange(int min, int max) const {
	if (min == max)
		return min;

	if (min > max)
		std::swap(min, max);

	return rand() % (max - min) + min;
}

UINT Utils::randomRange(UINT min, UINT max) const {
	if (min == max)
		return min;

	if (min > max)
		std::swap(min, max);

	return rand() % (max - min) + min;
}

int Utils::randomRangeExcept(int min, int max, int except) const {
	if (min == max)
		return min;

	if (min > max)
		std::swap(min, max);

	int val = rand() % (max - min) + min;

	if (val == except)
		val = (val - min + 1) % (max - min) + min;

	return val;
}

double Utils::randomRange(double min, double max) const {
	if (min >= max)
		return min;

	return random01() * (max - min) + min;
}

int Utils::random(int max) const {
	return rand() % max;
}
