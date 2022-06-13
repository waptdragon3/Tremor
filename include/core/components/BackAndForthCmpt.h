#pragma once
#include "core/Component.h"
#include "core/components/TransformCmpt.h"
#include "VMath.h"

struct BAFCmpt :public W3D::Components::Component
{
private:
	TransformCmpt* transform;
public:
	W3D::fVec3 pathStart, pathEnd;
	float pathLengthTime;
	void start() override;
	void update() override;
};