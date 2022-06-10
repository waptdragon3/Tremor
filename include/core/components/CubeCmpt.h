#pragma once
#include "core/Component.h"
#include "core/components/TransformCmpt.h"
#include "VMath.h"
#include "graphics/Shader.h"

struct CubeCmpt :public Component
{
private:
	struct Vertex
	{
		fVec3 position;
		fVec2 UV;
		Vertex();
		Vertex(fVec3 pos, fVec2 uv);
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
	Shader* shader;
};