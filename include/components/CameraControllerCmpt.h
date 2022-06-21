#pragma once
#include "w3d/component/Component.h"
#include "w3d/graphics/Camera.h"

#include "w3d/input/Input.h"
#include "w3d/util/Time.h"

struct CameraControllerCmpt : public W3D::Components::Component
{
	W3D::Graphics::Camera* camera;
	
	float minYaw = W3D::Math::degreesToRad(-80.0f);
	float maxYaw = W3D::Math::degreesToRad(80.0f);

	float xSensitivity = 1.0f;
	float ySensitivity = 1.0f;

	float moveSpeed = 5.0f;

	void update() override
	{
		W3D::Math::fVec2 movement;
		if (W3D::Input::Keyboard::isInputDown("forward"))	movement += W3D::Math::fVec2( 0.0f, 1.0f);
		if (W3D::Input::Keyboard::isInputDown("left"))		movement += W3D::Math::fVec2( 1.0f, 0.0f);
		if (W3D::Input::Keyboard::isInputDown("right"))		movement += W3D::Math::fVec2(-1.0f, 0.0f);
		if (W3D::Input::Keyboard::isInputDown("backward"))	movement += W3D::Math::fVec2( 0.0f,-1.0f);

		if (std::abs(movement.sqrMag()) < 0.5) return;

		W3D::Math::fVec3 dir = (W3D::Math::fVec3(movement.x, 0.0f, movement.y)).normalized();
		camera->position += dir * W3D::Time::DTime();

	}
};

