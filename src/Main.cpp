#include <glad/glad.h>

#include "VMath.h"
#include "graphics/GLFW.h"
#include "graphics/Window.h"
#include "graphics/Shader.h"
#include "graphics/Texture.h"


#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "core/MainManager.h"
#include "core/components/TransformCmpt.h"
#include "core/components/CubeCmpt.h"
#include "core/components/BackAndForthCmpt.h"

#include <random>

fVec3 randOnSphere(float radius, std::default_random_engine* generator, std::uniform_real_distribution<float>* distribution);

int main()
{
	GLFW::init();
	
	Window window(1280, 720, "Tremor");
	window.makeCurrentContext();


	gladLoadGL();
	glViewport(0, 0, 1280, 720);
	glEnable(GL_DEPTH_TEST);

	Texture t("resources/textures/Shadowfell.jpg");

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

	std::default_random_engine generator;
	std::uniform_real_distribution<float> distribution(0.0f, 1.0f);


	MainManager mm;

	float radius = 2;
	//set up scene
	for(int i = 0; i < 1000; i++)
	{
		Entity* e = mm.getEManager()->makeEntity();
		TransformCmpt* transform = mm.getCManager()->makeComponent<TransformCmpt>(e);
		CubeCmpt* cube = mm.getCManager()->makeComponent<CubeCmpt>(e);
		BAFCmpt* baf = mm.getCManager()->makeComponent<BAFCmpt>(e);

		cube->shader = &shader;

		fVec3 posA = randOnSphere(radius, &generator, &distribution);
		fVec3 posB = randOnSphere(radius, &generator, &distribution);

		
		baf->pathStart = posA;
		baf->pathEnd = posB;
		baf->pathLengthTime = 2.0f;
		
		//transform->position = posA;
		//transform->scale = fVec3(1.0f, 1.0f, 1.0f) * (distribution(generator) * 2);
	}


	mm.update();

	printf("Num Entities: %i\n", mm.getEManager()->numEntities());

	Transform proj = Transform::Identity() * Transform::Perspective(45.0f, 1280.0f / 720.0f, 0.1f, 100.0f);
	
	shader.use();
	shader.setMatrix("projection", proj);


	while (!window.shouldClose())
	{
		glClearColor(0.0, 0.0, 0.0, 1.0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		
		fVec3 offset;
		offset = offset + fVec3(3.0f, 0.0f, 0.0f) * static_cast<float>(sin(GLFW::getTime()));
		offset = offset + fVec3(0.0f, 3.0f, 0.0f) * static_cast<float>(cos(GLFW::getTime()));




		const float radius = 10.0f;
		float camX = sin(GLFW::getTime()) * radius;
		float camZ = cos(GLFW::getTime()) * radius;
		//Transform view = Transform::Identity() * Transform::Translate(fVec3(0.0f, 0.0f, -5.0f));

		Transform view = Transform::LookAt(fVec3(camX, 0.0, camZ), fVec3(), fVec3(0.0f, 1.0f, 0.0f));

		shader.setMatrix("view", view);

		t.bind();
		mm.update();


		GLFW::pollEvents();
		window.swapBuffers();
	}

	return 0;
}

fVec3 randOnSphere(float radius, std::default_random_engine* generator, std::uniform_real_distribution<float>* distribution)
{
	float u = distribution->operator()(*generator);
	float v = distribution->operator()(*generator);

	float theta = 2 * 3.14159f * u;
	float phi = std::acosf(2 * v - 1);
	fVec3 pos;
	pos.x = radius * std::sin(phi) * std::cos(theta);
	pos.y = radius * std::sin(phi) * std::sin(theta);
	pos.z = radius * std::cos(phi);

	return pos;
}
