#pragma once
#include "w3d/component/Component.h"
#include "components/TransformCmpt.h"
#include "w3d/math/fVec3.h"
#include "w3d/math/fVec2.h"
#include "w3d/graphics/Shader.h"

struct CubeCmpt :public W3D::Components::Component
{
private:
	struct Vertex
	{
		W3D::Math::fVec3 position;
		W3D::Math::fVec2 UV;
		Vertex();
		Vertex(W3D::Math::fVec3 pos, W3D::Math::fVec2 uv);
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