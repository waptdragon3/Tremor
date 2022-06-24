#pragma once

#include "w3d/component/Component.h"
#include "w3d/math/Mat4.h"
#include "w3d/math/Quaternion.h"


struct TransformCmpt : public W3D::Components::Component
{
public:
	W3D::Math::fVec3 position;
	W3D::Math::fVec3 scale = W3D::Math::fVec3::One();
	W3D::Math::Quaternion rotation;

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

	W3D::Math::Mat4 getMatrix()
	{
		W3D::Math::Mat4 t = rotation.toMatrix() * getScaleMat() * getTranslationMat();

		return t;
	}

	W3D::Math::fVec3 Forward()
	{
		return rotation.toMatrix() * W3D::Math::fVec3(0, 0, 1);
	}

	W3D::Math::fVec3 Up()
	{
		return rotation.toMatrix() * W3D::Math::fVec3(0, 1, 0);
	}

	W3D::Math::fVec3 Left()
	{
		return rotation.toMatrix() * W3D::Math::fVec3(1, 0, 0);
	}
};