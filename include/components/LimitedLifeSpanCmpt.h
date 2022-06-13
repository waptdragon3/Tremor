#pragma once
#include "w3d/component/Component.h"
#include "w3d/component/EntityManager.h"
#include "w3d/graphics/GLFW.h"

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