#pragma once

namespace W3D::Math
{

	struct fVec3
	{
		float x, y, z;
		fVec3(float _x, float _y, float _z);
		fVec3();

		float& operator[](int index);
		float sqrMag();
		float mag();

		static fVec3 cross(fVec3 u, fVec3 v);
		static float dot(fVec3 u, fVec3 v);

		fVec3 normalized();
		void normalize();

		//operators
		fVec3& operator+=(const fVec3& r);
		fVec3& operator-=(const fVec3& r);
		fVec3& operator*=(const float r);
		fVec3& operator/=(const float r);

		static fVec3 Zero();
		static fVec3 One();
		static fVec3 Up();
		static fVec3 Right();
		static fVec3 Fwd();
	};


	//operators
	fVec3 operator+(fVec3 u, fVec3 v);
	fVec3 operator-(fVec3 u, fVec3 v);
	fVec3 operator*(fVec3 v, float s);
	fVec3 operator/(fVec3 v, float s);
	//negate vector
	fVec3 operator-(fVec3 v);
}