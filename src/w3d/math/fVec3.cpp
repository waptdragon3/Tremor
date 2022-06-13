#include "w3d/math/fVec3.h"
#include <stdexcept>
#include <cmath>


namespace W3D::Math
{
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

	fVec3 fVec3::cross(fVec3 u, fVec3 v)
	{
		float i = u[1] * v[2] - u[2] * v[1];
		float j = u[2] * v[0] - u[0] * v[2];
		float k = u[0] * v[1] - u[1] * v[0];

		return fVec3(i, j, k);
	}

	float fVec3::dot(fVec3 u, fVec3 v)
	{
		return u.x * v.x + u.y * v.y + u.z * v.z;
	}

	fVec3 fVec3::normalized()
	{
		float l = this->mag();
		return fVec3(x / l, y / l, z / l);
	}

	void fVec3::normalize()
	{
		float l = this->mag();
		x /= l;
		y /= l;
		z /= l;
	}

	fVec3& fVec3::operator+=(fVec3& r)
	{
		this->x += r.x;
		this->y += r.y;
		this->z += r.z;
		return *this;
	}

	fVec3& fVec3::operator-=(fVec3& r)
	{
		this->x -= r.x;
		this->y -= r.y;
		this->z -= r.z;
		return *this;
	}

	fVec3& fVec3::operator*=(float r)
	{
		this->x *= r;
		this->y *= r;
		this->z *= r;
		return *this;
	}

	fVec3& fVec3::operator/=(float r)
	{
		this->x /= r;
		this->y /= r;
		this->z /= r;
		return *this;
	}

	fVec3 fVec3::Zero()
	{
		return fVec3(0.0f, 0.0f, 0.0f);
	}

	fVec3 fVec3::One()
	{
		return fVec3(1.0f, 1.0f, 1.0f);
	}

	fVec3 fVec3::Up()
	{
		return fVec3(0.0f, 1.0f, 0.0f);
	}

	fVec3 fVec3::Right()
	{
		return fVec3(1.0f, 0.0f, 0.0f);
	}

	fVec3 fVec3::Fwd()
	{
		return fVec3(0.0f, 0.0f, 1.0f);
	}

	fVec3 operator+(fVec3 u, fVec3 v) { return fVec3(u.x + v.x, u.y + v.y, u.z + v.z); }

	fVec3 operator-(fVec3 u, fVec3 v) { return fVec3(u.x - v.x, u.y - v.y, u.z - v.z); }

	fVec3 operator*(fVec3 v, float s) { return fVec3(v.x * s, v.y * s, v.z * s); }

	fVec3 operator/(fVec3 v, float s) { return fVec3(v.x / s, v.y / s, v.z / s); }

	fVec3 operator-(fVec3 v) { return fVec3(-v.x, -v.y, -v.z); }


}