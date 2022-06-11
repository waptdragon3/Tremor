#pragma once

#include "core/Component.h"

#include "VMath.h"


struct TransformCmpt : public Component
{
public:
	fVec3 position;
	fVec3 scale = fVec3::One();

	void start()
	{

	}

	Transform getTransform()
	{
		Transform t = Transform::Identity();
		
		t = t * Transform::Scale(scale) * Transform::Translate(position) ;

		return t;
	}
};