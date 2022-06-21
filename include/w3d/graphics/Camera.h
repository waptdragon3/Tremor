#pragma once
#include "w3d/math/fVec2.h"
#include "w3d/math/fVec3.h"
#include "w3d/math/Transform.h"

namespace W3D::Graphics
{
	class Camera
	{
	public:
		//position in world space
		W3D::Math::fVec3 position;
		//<Yaw, Pitch>
		W3D::Math::fVec2 eulerAngles;

		W3D::Math::Transform getViewMatrix()
		{
			W3D::Math::Transform t = W3D::Math::Transform::Identity();
			//translate
			t = t * W3D::Math::Transform::Translate(position);
			//yaw
			t = t * W3D::Math::Transform::Rotate(eulerAngles.x, W3D::Math::fVec3::Up());
			//pitch
			t = t * W3D::Math::Transform::Rotate(eulerAngles.y, -W3D::Math::fVec3::Right());


			return t;
		}

	};
}