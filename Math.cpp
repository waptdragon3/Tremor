#include "Math.h"
#include <stdexcept>
#include <cmath>

//fVec2

fVec2::fVec2(float _x, float _y) : x(_x), y(_y) {}
fVec2::fVec2() : x(0.0f), y(0.0f) {}

float& fVec2::operator[](int index)
{
	switch (index)
	{
	case 0: return x;
	case 1: return y;
	default:
		throw std::runtime_error("Vector index out of bounds");
		break;
	}
}

float fVec2::sqrMag() { return x * x + y * y; }
float fVec2::mag() { return std::sqrt(x * x + y * y); }



//fVec3

fVec3::fVec3(float _x, float _y, float _z) : x(_x), y(_y), z(_z) {}
fVec3::fVec3() : x(0.0f), y(0.0f), z(0.0f) {}

float& fVec3::operator[](int index)
{
	switch (index)
	{
	case 0: return x;
	case 1: return y;
	case 2: return z;
	default:
		throw std::runtime_error("Vector index out of bounds");
		break;
	}
}

float fVec3::sqrMag() { return x * x + y * y + z * z; }
float fVec3::mag() { return std::sqrt(x * x + y * y + z * z); }



//iVec2

iVec2::iVec2(int _x, int _y) : x(_x), y(_y) {}
iVec2::iVec2() : x(0), y(0) {}

int& iVec2::operator[](int index)
{
	switch (index)
	{
	case 0: return x;
	case 1: return y;
	default:
		throw std::runtime_error("Vector index out of bounds");
		break;
	}
}




//iVec3

iVec3::iVec3(int _x, int _y, int _z) : x(_x), y(_y), z(_z) {}
iVec3::iVec3() : x(0), y(0), z(0) {}

int& iVec3::operator[](int index)
{
	switch (index)
	{
	case 0: return x;
	case 1: return y;
	case 2: return z;
	default:
		throw std::runtime_error("Vector index out of bounds");
		break;
	}
}