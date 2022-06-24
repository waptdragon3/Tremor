#pragma once
#include "w3d/math/fVec2.h"
#include "w3d/math/fVec3.h"
#include "w3d/math/Mat4.h"
#include "w3d/math/Quaternion.h"

namespace W3D::Graphics
{
	class Camera
	{
	public:

		W3D::Math::fVec3 position;
		W3D::Math::fVec3 scale = W3D::Math::fVec3::One();
		W3D::Math::Quaternion rotation;

		W3D::Math::Mat4 view;
		W3D::Math::Mat4 perspective;

		W3D::Math::Mat4 getTranslationMat()
		{
			W3D::Math::Mat4 mat;
			mat.get(3, 0) = position.x;
			mat.get(3, 1) = position.y;
			mat.get(3, 2) = position.z;
			return mat;
		}

		W3D::Math::Mat4 getScaleMat()
		{
			W3D::Math::Mat4 mat;
			mat.get(0, 0) = scale.x;
			mat.get(1, 1) = scale.y;
			mat.get(2, 2) = scale.z;
			return mat;
		}

		W3D::Math::Mat4 getViewMatrix()
		{
			//W3D::Math::Mat4 t = getTranslationMat() * getScaleMat() * rotation.toMatrix();

			return view;
		}

	};
}