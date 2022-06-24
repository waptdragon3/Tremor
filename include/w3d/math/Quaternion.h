#pragma once
#include "w3d/math/fVec3.h"
#include "w3d/math/Mat4.h"

namespace W3D::Math
{
	class Quaternion
	{
	private:
		float W, X, Y, Z;

		void renormalize();
		float sqrMag();

		friend Quaternion operator*(Quaternion q1, Quaternion q2);

		friend Quaternion operator-(Quaternion v);


	public:
		void rotateAround(fVec3 axis, float degrees);
		void reset();
		Quaternion();

		Mat4 toMatrix();

		//Quaternion& operator*= (Quaternion q);
	};

	Quaternion operator*(Quaternion q1, Quaternion q2);
	//negate Quaternion
	Quaternion operator-(Quaternion v);
}