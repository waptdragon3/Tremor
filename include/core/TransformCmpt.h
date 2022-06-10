#pragma once

#include "core/Component.h"

#include "VMath.h"


struct TransformCmpt : public Component
{
public:
	fVec3 position;

	Transform getTransform()
	{
		Transform t = Transform::Identity();
		
		t = t * Transform::Translate(position);

		return t;
	}
};