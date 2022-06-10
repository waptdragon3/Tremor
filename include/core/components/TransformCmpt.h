#pragma once

#include "core/Component.h"

#include "VMath.h"


struct TransformCmpt : public Component
{
public:
	fVec3 position;
	fVec3 scale;

	void start()
	{
		scale = fVec3(1.0f, 1.0f, 1.0f);
	}

	Transform getTransform()
	{
		Transform t = Transform::Identity();
		
		t = t * Transform::Translate(position);

		return t;
	}
};