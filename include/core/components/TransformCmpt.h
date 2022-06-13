#pragma once

#include "core/Component.h"

#include "VMath.h"


struct TransformCmpt : public W3D::Components::Component
{
public:
	W3D::fVec3 position;
	W3D::fVec3 scale = W3D::fVec3::One();

	void start()
	{

	}

	W3D::Transform getTransform()
	{
		W3D::Transform t = W3D::Transform::Identity();
		
		t = t * W3D::Transform::Scale(scale) * W3D::Transform::Translate(position) ;

		return t;
	}
};