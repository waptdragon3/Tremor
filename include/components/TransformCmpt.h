#pragma once

#include "w3d/component/Component.h"
#include "w3d/math/Transform.h"


struct TransformCmpt : public W3D::Components::Component
{
public:
	W3D::Math::fVec3 position;
	W3D::Math::fVec3 scale = W3D::Math::fVec3::One();

	void start()
	{

	}

	W3D::Math::Transform getTransform()
	{
		W3D::Math::Transform t = W3D::Math::Transform::Identity();
		
		t = t * W3D::Math::Transform::Scale(scale) * W3D::Math::Transform::Translate(position) ;

		return t;
	}
};