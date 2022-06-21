#pragma once
#include "w3d/component/Component.h"
#include "w3d/component/EntityManager.h"
#include "w3d/util/Time.h"

struct LimitedLifeSpaceCmpt : public W3D::Components::Component
{
public:
	float time;
	float totalTime;

	void start() override
	{
		totalTime = 0.0f;
	}

	void update() override
	{
		totalTime += W3D::Time::DTime();

		if (totalTime > time)
		{
			this->eManager->removeEntity(this->controllingEntity);
		}
	}
};