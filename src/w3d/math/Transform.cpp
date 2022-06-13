#include "w3d/math/Transform.h"
#include <stdexcept>
#include <cmath>

namespace W3D::Math
{
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