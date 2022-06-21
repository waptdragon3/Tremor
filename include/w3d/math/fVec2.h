#pragma once

namespace W3D::Math
{

	struct fVec2
	{
		float x, y;
		fVec2(float _x, float _y);
		fVec2();

		float& operator[](int index);
		float sqrMag();
		float mag();

		fVec2 normalized();
		void normalize();

		//operators
		fVec2& operator+=(const fVec2& r);
		fVec2& operator-=(const fVec2& r);
		fVec2& operator*=(const float r);
		fVec2& operator/=(const float r);

		static fVec2 Zero();
		static fVec2 One();
	};


	//operators
	fVec2 operator+(fVec2 u, fVec2 v);
	fVec2 operator-(fVec2 u, fVec2 v);
	fVec2 operator*(fVec2 v, float s);
	fVec2 operator/(fVec2 v, float s);
	//negate vector
	fVec2 operator-(fVec2 v);
}