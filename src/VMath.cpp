#include "VMath.h"
#include <stdexcept>
#include <cmath>

namespace W3D
{

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
		return *this;
	}

	fVec3& fVec3::operator-=(fVec3& r)
	{
		this->x -= r.x;
		this->y -= r.y;
		return *this;
	}

	fVec3& fVec3::operator*=(float r)
	{
		this->x *= r;
		this->y *= r;
		return *this;
	}

	fVec3& fVec3::operator/=(float r)
	{
		this->x /= r;
		this->y /= r;
		return *this;
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

	fVec2 operator+(fVec2 u, fVec2 v) { return fVec2(u.x + v.x, u.y + v.y); }

	fVec2 operator-(fVec2 u, fVec2 v) { return fVec2(u.x - v.x, u.y - v.y); }

	fVec2 operator*(fVec2 v, float s) { return fVec2(v.x * s, v.y * s); }

	fVec2 operator/(fVec2 v, float s) { return fVec2(v.x / s, v.y / s); }

	fVec2 operator-(fVec2 v) { return fVec2(-v.x, -v.y); }

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

	float degreesToRad(float degrees)
	{
		return degrees * 3.14159f / 180.0f;
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
			throw std::runtime_error("Matrix index out of bounds");
	}

	float& Transform::get(unsigned int i, unsigned int j)
	{
		if (i < 4 && j < 4)
		{
			return items[i * 4 + j];
		}
		throw std::runtime_error("Matrix index out of bounds");
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
		t.get(3, 0) = pos.x;
		t.get(3, 1) = pos.y;
		t.get(3, 2) = pos.z;
		return t;
	}

	Transform Transform::Rotate(float theta, fVec3 axis)
	{
		Transform t;
		float cos = std::cos(theta);
		float sin = std::sin(theta);

		axis = axis / axis.mag();

		//some magic rotation bullshit
		t.get(0, 0) = (axis.x * axis.x) * (1 - cos) + cos;			//index 0
		t.get(1, 0) = axis.x * axis.y * (1 - cos) - axis.z * sin;	//index 4
		t.get(2, 0) = axis.x * axis.z * (1 - cos) + axis.y * sin;	//index 8

		t.get(0, 1) = axis.y * axis.x * (1 - cos) + axis.z * sin;	//index 1
		t.get(1, 1) = (axis.y * axis.y) * (1 - cos) + cos;			//index 5
		t.get(2, 1) = axis.y * axis.z * (1 - cos) - axis.x * sin;	//index 9

		t.get(0, 2) = axis.x * axis.z * (1 - cos) - axis.y * sin;	//index 2
		t.get(1, 2) = axis.y * axis.z * (1 - cos) + axis.x * sin;	//index 6
		t.get(2, 2) = (axis.z * axis.z) * (1 - cos) + cos;			//index 10

		t.get(3, 3) = 1;											//index 15

		return t;
	}

	Transform Transform::Perspective(float fov, float aspectRatio, float near, float far)
	{
		Transform t;
		float rad = degreesToRad(fov);
		float cot = std::cos(rad / 2.0f) / std::sin(rad / 2.0f);

		t.get(0, 0) = cot / aspectRatio;				//index 0
		t.get(1, 1) = cot;								//index 5

		t.get(2, 2) = (far + near) / (near - far);		//index 10
		t.get(3, 2) = (2 * far * near) / (near - far);	//index 14
		t.get(2, 3) = -1;								//index 11

		return t;
	}

	Transform Transform::Scale(fVec3 scaleFactors)
	{
		Transform t;
		t.get(0, 0) = scaleFactors.x;
		t.get(1, 1) = scaleFactors.y;
		t.get(2, 2) = scaleFactors.z;
		t.get(3, 3) = 1.0f;
		return t;
	}

	Transform Transform::LookAt(fVec3 position, fVec3 target, fVec3 up)
	{
		Transform t1 = Transform::Identity();

		up.normalize();

		fVec3 f = (target - position).normalized();
		fVec3 s = (fVec3::cross(f, up)).normalized();
		fVec3 u = fVec3::cross(s, f);

		t1.get(0, 0) = s.x;
		t1.get(1, 0) = s.y;
		t1.get(2, 0) = s.z;

		t1.get(0, 1) = u.x;
		t1.get(1, 1) = u.y;
		t1.get(2, 1) = u.z;

		t1.get(0, 2) = -f.x;
		t1.get(1, 2) = -f.y;
		t1.get(2, 2) = -f.z;

		t1.get(3, 0) = -fVec3::dot(s, position);
		t1.get(3, 1) = -fVec3::dot(u, position);
		t1.get(3, 2) = fVec3::dot(f, position);


		return t1;
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

	float* Transform::getItems()
	{
		return items;
	}

}