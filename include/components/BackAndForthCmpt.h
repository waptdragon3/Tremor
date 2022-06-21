#pragma once
#include "w3d/component/Component.h"
#include "components/TransformCmpt.h"
#include "w3d/math/fVec3.h"

struct BAFCmpt :public W3D::Components::Component
{
private:
	TransformCmpt* transform;
public:
	W3D::Math::fVec3 pathStart, pathEnd;
	float pathLengthTime;
	float totalTime;
	void start() override;
	void update() override;
};