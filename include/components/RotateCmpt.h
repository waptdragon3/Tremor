#pragma once
#include "w3d/component/Component.h"
#include "components/TransformCmpt.h"
#include "w3d/util/Time.h"
#include "w3d/component/ComponentManager.h"


struct RotateCmpt : public W3D::Components::Component
{
	TransformCmpt* transform = nullptr;
	float turnRate = 90.0f;

	void start() override
	{
		transform = dynamic_cast<TransformCmpt*>(cManager->getComponentTypeOnEntity<TransformCmpt>(controllingEntity));
	}
	void update() override
	{
		transform->rotation.rotateAround(W3D::Math::fVec3::Up(), turnRate * W3D::Time::DTime());
	}
};