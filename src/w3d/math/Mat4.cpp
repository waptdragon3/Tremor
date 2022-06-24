#include "w3d/math/Mat4.h"
#include <stdexcept>
#include <cmath>

namespace W3D::Math
{
	float degreesToRad(float degrees)
	{
		return degrees * 3.14159f / 180.0f;
	}

	Mat4::Mat4()
	{
		for (int i = 0; i < 16; i++)
			items[i] = 0.0f;
		get(0, 0) = 1;
		get(1, 1) = 1;
		get(2, 2) = 1;
		get(3, 3) = 1;
	}

	float& Mat4::operator[](unsigned int index)
	{
		if (index < 16)
			return items[index];
		else
			throw std::runtime_error("Matrix index out of bounds");
	}

	float& Mat4::get(unsigned int i, unsigned int j)
	{
		if (i < 4 && j < 4)
		{
			return items[i * 4 + j];
		}
		throw std::runtime_error("Matrix index out of bounds");
	}

	Mat4 Mat4::Identity()
	{
		Mat4 t;
		t.get(0, 0) = 1;
		t.get(1, 1) = 1;
		t.get(2, 2) = 1;
		t.get(3, 3) = 1;
		return t;
	}

	Mat4 Mat4::Perspective(float fov, float aspectRatio, float near, float far)
	{
		Mat4 t;
		float rad = degreesToRad(fov);
		float cot = std::cos(rad / 2.0f) / std::sin(rad / 2.0f);

		t.get(0, 0) = cot / aspectRatio;				//index 0
		t.get(1, 1) = cot;								//index 5

		t.get(2, 2) = (far + near) / (near - far);		//index 10
		t.get(3, 2) = (2 * far * near) / (near - far);	//index 14
		t.get(2, 3) = -1;								//index 11

		return t;
	}

	Mat4 Mat4::Scale(fVec3 scaleFactors)
	{
		Mat4 t;
		t.get(0, 0) = scaleFactors.x;
		t.get(1, 1) = scaleFactors.y;
		t.get(2, 2) = scaleFactors.z;
		t.get(3, 3) = 1.0f;
		return t;
	}

	Mat4 Mat4::LookAt(fVec3 position, fVec3 target, fVec3 up)
	{
		Mat4 t1 = Mat4::Identity();

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

	Mat4 Mat4::operator*(Mat4 t)
	{
		Mat4 c;

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

	fVec3 Mat4::operator*(fVec3 v)
	{
		fVec3 r;
		
		r.x = get(0, 0)*v.x + get(1, 0)*v.y + get(2, 0)*v.z;
		r.y = get(0, 1)*v.x + get(1, 1)*v.y + get(2, 1)*v.z;
		r.z = get(0, 2)*v.x + get(1, 2)*v.y + get(2, 2)*v.z;

		return r;
	}

	float* Mat4::getItems()
	{
		return items;
	}
}