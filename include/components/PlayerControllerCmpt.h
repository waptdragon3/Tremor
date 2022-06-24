#pragma once
#include "w3d/component/Component.h"
#include "w3d/math/fVec2.h"
#include "components/TransformCmpt.h"
#include "components/CameraControllerCmpt.h"

struct PlayerControllerCmpt : public W3D::Components::Component
{
	TransformCmpt* transform = nullptr;
	CameraControllerCmpt* cameraController = nullptr;

	W3D::Math::fVec2 rot;

	float minYaw = W3D::Math::degreesToRad(-80.0f);
	float maxYaw = W3D::Math::degreesToRad(80.0f);

	float xSensitivity = 90.0f;
	float ySensitivity = 90.0f;

	float moveSpeed = 5.0f;


	void start() override;
	void update() override;
};