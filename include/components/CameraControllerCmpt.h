#pragma once
#include "w3d/component/Component.h"
#include "w3d/graphics/Camera.h"
#include "components/TransformCmpt.h"

#include "w3d/input/Input.h"
#include "w3d/util/Time.h"
#include <iostream>

struct CameraControllerCmpt : public W3D::Components::Component
{
	W3D::Graphics::Camera* camera = nullptr;
	TransformCmpt* transform = nullptr;

	float yaw;
	float pitch;

	void start() override;
	void update() override;
};

