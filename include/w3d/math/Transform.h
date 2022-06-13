#pragma once
#include "w3d/math/fVec3.h"

namespace W3D::Math
{
	class Transform
	{
	private:
		float items[16];
		Transform();
	public:

		float& operator[](unsigned int index);

		float& get(unsigned int i, unsigned int j);

		static Transform Identity();
		static Transform Translate(fVec3 pos);
		static Transform Rotate(float thetaRad, fVec3 axis);
		static Transform Perspective(float fov, float aspectRatio, float near, float far);
		static Transform Scale(fVec3 scaleFactors);

		static Transform LookAt(fVec3 position, fVec3 target, fVec3 up);

		Transform operator* (Transform t);
		float* getItems();

	};

	float degreesToRad(float degrees);
}