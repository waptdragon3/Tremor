#pragma once
#include "core/Component.h"
#include "core/components/TransformCmpt.h"
#include "VMath.h"

struct BAFCmpt :public Component
{
private:
	TransformCmpt* transform;
public:
	fVec3 pathStart, pathEnd;
	float pathLengthTime;
	void start() override;
	void update() override;
};