#include <glad/glad.h>

#include "VMath.h"
#include "graphics/GLFW.h"
#include "graphics/Window.h"
#include "graphics/Shader.h"
#include "graphics/Texture.h"


#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


int main()
{
	GLFW::init();
	
	Window window(1280, 720, "Tremor");
	window.makeCurrentContext();


	gladLoadGL();
	glViewport(0, 0, 1280, 720);
	glEnable(GL_DEPTH_TEST);

	Texture t("resources/textures/Shadowfell.jpg");

	float vertices[] = {
		// positions            // texture coords
		 0.5f,  0.5f, -0.5f,     1.0f, 1.0f,   // Back top right
		 0.5f, -0.5f, -0.5f,     1.0f, 0.0f,   // Back bottom right
		-0.5f, -0.5f, -0.5f,     0.0f, 0.0f,   // Back bottom left
		-0.5f,  0.5f, -0.5f,     0.0f, 1.0f,   // Back top left 

		 0.5f,  0.5f, 0.5f,      0.0f, 0.0f,   // front top right
		 0.5f, -0.5f, 0.5f,      1.0f, 1.0f,   // front bottom right
		-0.5f, -0.5f, 0.5f,      1.0f, 0.0f,   // front bottom left
		-0.5f,  0.5f, 0.5f,      0.0f, 1.0f    // front top left 
	};
	unsigned int indices[] = {  // note that we start from 0!
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

	const char* vertexShaderSource = "#version 330 core\n"
		"layout(location = 0) in vec3 aPos;\n"
		"layout(location = 1) in vec2 aTexCoord;\n"
		"out vec2 TexCoord;\n"
		"uniform mat4 model;\n"
		"uniform mat4 view;\n"
		"uniform mat4 projection;\n"
		"void main()\n"
		"{\n"
		"	gl_Position = projection * view * model * vec4(aPos, 1.0);\n"
		"	TexCoord = aTexCoord;\n"
		"}\n";

	const char* fragmentShaderSource = "#version 330 core\n"
		"out vec4 FragColor;\n"
		"in vec2 TexCoord;\n"
		"uniform sampler2D ourTexture;"
		"void main()\n"
		"{\n"
		"	FragColor = texture(ourTexture, TexCoord);\n"
		"}\0";

	Shader shader(vertexShaderSource, fragmentShaderSource);

	unsigned int VBO, VAO, EBO;
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
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	//set UV coords
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	

	
	while (!window.shouldClose())
	{
		glClearColor(0.0, 0.0, 0.0, 1.0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		
		fVec3 offset;
		offset = offset + fVec3(3.0f, 0.0f, 0.0f) * static_cast<float>(sin(GLFW::getTime()));
		offset = offset + fVec3(0.0f, 3.0f, 0.0f) * static_cast<float>(cos(GLFW::getTime()));

		shader.use();

		Transform model = Transform::Identity() * Transform::Rotate(GLFW::getTime(), fVec3(0.5f, 1.0f, 0.0f));
		Transform view = Transform::Identity() * Transform::Translate(fVec3(0.0f, 0.0f, -5.0f));
		Transform proj = Transform::Identity() * Transform::Perspective(45.0f, 1280.0f / 720.0f, 0.1f, 100.0f);


		shader.setMatrix("model", model);
		shader.setMatrix("view", view);
		shader.setMatrix("projection", proj);


		//activate shader
		shader.use();
		//bind texture
		t.bind();
		//bind VAO
		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);


		GLFW::pollEvents();
		window.swapBuffers();
	}

	return 0;
}