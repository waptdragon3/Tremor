#pragma once
#include "core/Component.h"
#include "core/EntityManager.h"
#include "graphics/GLFW.h"

struct LimitedLifeSpaceCmpt : public W3D::Components::Component
{
public:
	float time;
	void update() override
	{
		if (W3D::Graphics::GLFW::getTime() > time)
		{
			this->eManager->removeEntity(this->controllingEntity);
		}
	}
};