#pragma once
#include "w3d/component/Component.h"
#include "w3d/graphics/Mesh.h"
#include "w3d/graphics/Shader.h"
#include "components/TransformCmpt.h"

struct ModelCmpt : public W3D::Components::Component
{
	W3D::Graphics::Model* model = nullptr;
	W3D::Graphics::Shader* shader = nullptr;

	TransformCmpt* transform = nullptr;

	void start() override;
	void update() override;
};