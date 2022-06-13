#pragma once
#include "core/Component.h"
#include "core/components/TransformCmpt.h"
#include "VMath.h"
#include "graphics/Shader.h"

struct CubeCmpt :public W3D::Components::Component
{
private:
	struct Vertex
	{
		W3D::fVec3 position;
		W3D::fVec2 UV;
		Vertex();
		Vertex(W3D::fVec3 pos, W3D::fVec2 uv);
	};

	Vertex vertices[8];
	int numVertices;
	unsigned int indices[36];
	int numIndices;
	unsigned int VAO;
	TransformCmpt* transform;
public:
	void start() override;
	void update() override;
	void finalize() override;
	W3D::Graphics::Shader* shader;
};