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

fVec3::fVec3(fVec2 v) : x(v.x), y(v.y), z(0.0f) {}

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

fVec2 operator+(fVec2 u, fVec2 v) { return fVec2(u.x + v.x, u.y + v.y); }

fVec2 operator-(fVec2 u, fVec2 v) {return fVec2(u.x - v.x, u.y - v.y); }

fVec2 operator*(fVec2 v, float s) {return fVec2(v.x * s, v.y * s); }

fVec2 operator/(fVec2 v, float s) {return fVec2(v.x / s, v.y / s); }

fVec2 operator-(fVec2 v) {return fVec2(-v.x, -v.y); }

fVec2& operator+=(fVec2& l, fVec2& r)
{
	l.x += r.x;
	l.y += r.y;
	return l;
}

fVec2& operator-=(fVec2& l, fVec2& r)
{
	l.x -= r.x;
	l.y -= r.y;
	return l;
}

fVec2& operator*=(fVec2& l, float& r)
{
	l.x *= r;
	l.y *= r;
	return l;
}

fVec2& operator/=(fVec2& l, float& r)
{
	l.x /= r;
	l.y /= r;
	return l;
}


fVec3 operator+(fVec3 u, fVec3 v) { return fVec3(u.x + v.x, u.y + v.y, u.z + v.z); }

fVec3 operator-(fVec3 u, fVec3 v) { return fVec3(u.x - v.x, u.y - v.y, u.z - v.z); }

fVec3 operator*(fVec3 v, float s) { return fVec3(v.x * s, v.y * s, v.z * s); }

fVec3 operator/(fVec3 v, float s) { return fVec3(v.x / s, v.y / s, v.z / s); }

fVec3 operator-(fVec3 v) { return fVec2(-v.x, -v.y); }

fVec3& operator+=(fVec3& l, fVec3& r)
{
	l.x += r.x;
	l.y += r.y;
	l.z += r.z;
	return l;
}

fVec3& operator-=(fVec3& l, fVec3& r)
{
	l.x -= r.x;
	l.y -= r.y;
	l.z -= r.z;
	return l;
}

fVec3& operator*=(fVec3& l, float& r)
{
	l.x *= r;
	l.y *= r;
	l.z *= r;
	return l;
}

fVec3& operator/=(fVec3& l, float& r)
{
	l.x /= r;
	l.y /= r;
	l.z /= r;
	return l;
}

Transform::Transform()
{
	for (int i = 0; i < 16; i++)
		items[i] = 0.0f;
}

float& Transform::operator[](unsigned int index)
{
	if (index < 16)
		return items[index];
	else
		throw std::runtime_error("Vector index out of bounds");
}

float& Transform::get(unsigned int i, unsigned int j)
{
	if (i < 4 && j < 4)
	{
		return items[i * 4 + j];
	}
}

Transform Transform::Identity()
{
	Transform t;
	t.get(0, 0) = 1;
	t.get(1, 1) = 1;
	t.get(2, 2) = 1;
	t.get(3, 3) = 1;
	return t;
}

Transform Transform::Translate(fVec3 pos)
{
	Transform t = Transform::Identity();
	t.get(0, 3) = pos.x;
	t.get(1, 3) = pos.y;
	t.get(2, 3) = pos.z;
	return t;
}

Transform Transform::Rotate(float theta, fVec3 axis)
{
	Transform t = Transform::Identity();
	float cos = std::cos(theta);
	float sin = std::sin(theta);
	//some magic rotation bullshit
	t.get(0, 0) = cos + (axis.x * axis.x) * (1 - cos);
	t.get(0, 1) = axis.x * axis.y * (1 - cos) - axis.z * sin;
	t.get(0, 2) = axis.x * axis.z * (1 - cos) + axis.y * sin;

	t.get(1, 0) = axis.y * axis.x * (1 - cos) + axis.z * sin;
	t.get(1, 1) = cos + (axis.y * axis.y) * (1 - cos);
	t.get(1, 2) = axis.y * axis.z * (1 - cos) + axis.y * sin;

	t.get(2, 0) = axis.z * axis.x * (1 - cos) - axis.y * sin;
	t.get(2, 1) = axis.z * axis.y * (1 - cos) + axis.x * sin;
	t.get(2, 2) = cos + (axis.z * axis.z) * (1 - cos);

	t.get(3, 3) = 1;

	return t;
}

Transform Transform::operator*(Transform t)
{
	Transform c;

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			float num = 0;
			for (int k = 0; k < 4; k++)
			{
				num += this->get(i, k) * t.get(k, j);
			}
			c.get(i, j) = num;
		}
	}
	return c;
}
