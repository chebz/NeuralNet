#pragma once
#include <stdlib.h>
#include <time.h> 
#include <algorithm>

#define UINT unsigned int
#define UTILS Utils::getInstance()

class Utils {
#pragma region Singleton
public:
	static Utils& getInstance() {
		static Utils instance;
		return instance;
	}

private:
	Utils();

	Utils(Utils const&) = delete;

	void operator=(Utils const&) = delete;
#pragma endregion Singleton

private:
	bool mRandomSeeded;

public:
	double random01() const;

	int randomRange(int min, int max) const;

	UINT randomRange(UINT min, UINT max) const;

	int randomRangeExcept(int min, int max, int except) const;

	double randomRange(double min, double max) const;

	int random(int max) const;

	
};

template <class T>
T clamp(const T& value, const T& min, const T& max) {
	return std::max(min, std::min(value, max));
}