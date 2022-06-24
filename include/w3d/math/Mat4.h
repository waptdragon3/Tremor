#pragma once
#include "w3d/math/fVec3.h"

namespace W3D::Math
{
	class Mat4
	{
	private:
		float items[16];
	public:
		Mat4();

		float& operator[](unsigned int index);

		float& get(unsigned int i, unsigned int j);
		static Mat4 Identity();
		Mat4 operator* (Mat4 t);
		fVec3 operator* (fVec3 v);
		float* getItems();
		static Mat4 Scale(fVec3 scaleFactors);
		static Mat4 Perspective(float fov, float aspectRatio, float near, float far);
		static Mat4 LookAt(fVec3 position, fVec3 target, fVec3 up);
	private:



	};

	float degreesToRad(float degrees);
}