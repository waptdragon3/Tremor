#include "w3d/math/fVec2.h"
#include <stdexcept>
#include <cmath>

namespace W3D::Math
{

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

	fVec2 fVec2::normalized()
	{
		float l = this->mag();
		return fVec2(x / l, y / l);
	}

	void fVec2::normalize()
	{
		float l = this->mag();
		x /= l;
		y /= l;
	}

	fVec2& fVec2::operator+=(const fVec2& r)
	{
		this->x += r.x;
		this->y += r.y;
		return *this;
	}

	fVec2& fVec2::operator-=(const fVec2& r)
	{
		this->x -= r.x;
		this->y -= r.y;
		return *this;
	}

	fVec2& fVec2::operator*=(const float r)
	{
		this->x *= r;
		this->y *= r;
		return *this;
	}

	fVec2& fVec2::operator/=(const float r)
	{
		this->x /= r;
		this->y /= r;
		return *this;
	}

	fVec2 fVec2::Zero()
	{
		return fVec2(0.0f, 0.0f);
	}

	fVec2 fVec2::One()
	{
		return fVec2(1.0f, 1.0f);
	}



	fVec2 operator+(fVec2 u, fVec2 v) { return fVec2(u.x + v.x, u.y + v.y); }

	fVec2 operator-(fVec2 u, fVec2 v) { return fVec2(u.x - v.x, u.y - v.y); }

	fVec2 operator*(fVec2 v, float s) { return fVec2(v.x * s, v.y * s); }

	fVec2 operator/(fVec2 v, float s) { return fVec2(v.x / s, v.y / s); }

	fVec2 operator-(fVec2 v) { return fVec2(-v.x, -v.y); }
}