#include "core/components/CubeCmpt.h"
#include "core/ComponentManager.h"
#include <glad/glad.h>


void CubeCmpt::start()
{
	//initialize vertices and indices
	{
		numVertices = 8;
		vertices[0] = Vertex(fVec3(0.5f, 0.5f, -0.5f), fVec2(1.0f, 1.0f));
		vertices[1] = Vertex(fVec3(0.5f, -0.5f, -0.5f), fVec2(0.0f, 1.0f));
		vertices[2] = Vertex(fVec3(-0.5f, -0.5f, -0.5f), fVec2(0.0f, 0.0f));
		vertices[3] = Vertex(fVec3(-0.5f, 0.5f, -0.5f), fVec2(0.0f, 1.0f));

		vertices[4] = Vertex(fVec3(0.5f, 0.5f, 0.5f), fVec2(0.0f, 0.0f));
		vertices[5] = Vertex(fVec3(0.5f, -0.5f, 0.5f), fVec2(1.0f, 1.0f));
		vertices[6] = Vertex(fVec3(-0.5f, -0.5f, 0.5f), fVec2(1.0f, 0.0f));
		vertices[7] = Vertex(fVec3(-0.5f, 0.5f, 0.5f), fVec2(0.0f, 1.0f));


		unsigned int _indices[36] = {  // note that we start from 0!
			0, 1, 3,   // first triangle
			1, 2, 3,   // second triangle
			0, 1, 4,
			1, 4, 5,
			0, 3, 4,
			3, 4, 7,
			3, 2, 6,
			3, 6, 7,
			4, 5, 6,
			4, 6, 7,
			1, 2, 5,
			2, 5, 6
		};

		for (int i = 0; i < 36; i++)
		{
			indices[i] = _indices[i];
		}
		numIndices = 36;
	}

	unsigned int VBO, EBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	// 1. bind Vertex Array Object
	glBindVertexArray(VAO);
	// 2. copy our vertices array in a buffer for OpenGL to use
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	// 3. copy our index array in a element buffer for OpenGL to use
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	// 4. then set the vertex attributes pointers
	//set position
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
	glEnableVertexAttribArray(0);
	//set UV coords
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(sizeof(fVec3)));
	glEnableVertexAttribArray(1);

	transform = cManager->getComponentTypeOnEntity<TransformCmpt>(controllingEntity);
}

void CubeCmpt::update()
{
	Transform t = transform->getTransform();
	shader->use();
	shader->setMatrix("model", t);

	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, numIndices, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}

void CubeCmpt::finalize()
{
	
}

CubeCmpt::Vertex::Vertex()
{
}

CubeCmpt::Vertex::Vertex(fVec3 pos, fVec2 uv): position(pos), UV(uv)
{
}
