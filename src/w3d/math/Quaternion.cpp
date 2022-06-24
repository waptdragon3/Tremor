#include "w3d/math/Quaternion.h"
#include <cmath>

namespace W3D::Math
{

	void Quaternion::renormalize()
	{
		float magnitude = std::sqrt(W * W + X * X + Y * Y + Z * Z);

		W /= magnitude;
		X /= magnitude;
		Y /= magnitude;
		Z /= magnitude;
	}

	float Quaternion::sqrMag()
	{
		return W * W + X * X + Y * Y + Z * Z;
	}

	void Quaternion::rotateAround(fVec3 axis, float degrees)
	{
		float radians = degrees * 3.14159f / 180.0f;

		Quaternion local;
		local.W = std::cosf(radians / 2);
		local.X = axis.x * std::sinf(radians / 2);
		local.Y = axis.y * std::sinf(radians / 2);
		local.Z = axis.z * std::sinf(radians / 2);

		Quaternion tmp = operator*(local, *this);
		
		W = tmp.W;
		X = tmp.X;
		Y = tmp.Y;
		Z = tmp.Z;
	}

	void Quaternion::reset()
	{
		W = 1;
		X = 0;
		Y = 0;
		Z = 0;
	}

	Quaternion::Quaternion()
	{
		reset();
	}

	Mat4 Quaternion::toMatrix()
	{
		Mat4 mat;
		mat[0]  = 1 - 2 * (Y*Y + Z*Z);
		mat[1]  = 	  2 * (X*Y - Z*W);
		mat[2]  =	  2 * (X*Z + Y*W);

		mat[4]  =	  2 * (X*Y + Z*W);
		mat[5]  = 1 - 2 * (X*X + Z*Z);
		mat[6]  =	  2 * (Y*Z - X*W);

		mat[8]  =	  2 * (X*Z - Y*W);
		mat[9]  =	  2 * (Y*Z + X*W);
		mat[10] = 1 - 2 * (X*X + Y*Y);

		mat[3] = mat[7] = mat[11] = mat[12] = mat[13] = mat[14] = 0;
		mat[15] = 1;

		return mat;
	}

	Quaternion operator*(Quaternion q1, Quaternion q2)
	{
		Quaternion r;
		
		r.W = (q1.W*q2.W - q1.X*q2.X - q1.Y*q2.Y - q1.Z*q2.Z);
		r.X = (q1.W*q2.X + q1.X*q2.W + q1.Y*q2.Z - q1.Z*q2.Y);
		r.Y = (q1.W*q2.Y - q1.X*q2.Z + q1.Y*q2.W + q1.Z*q2.X);		
		r.Z = (q1.W*q2.Z + q1.X*q2.Y - q1.Y*q2.X + q1.Z*q2.W);



		//value is too far from unit vector. renormalize
		if (std::abs(r.sqrMag() - 1) > 0.05f) r.renormalize();
		return r;
	}

	Quaternion operator-(Quaternion v)
	{
		Quaternion q;
		q.X = -v.X;
		q.Y = -v.Y;
		q.Z = -v.Z;
		q.W = -v.W;
		return q;
	}


}