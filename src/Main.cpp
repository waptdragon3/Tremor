#include <glad/glad.h>

#include "w3d/math/fVec3.h"
#include "w3d/graphics/GLFW.h"
#include "w3d/graphics/Window.h"
#include "w3d/graphics/Shader.h"
#include "w3d/graphics/Texture.h"


#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "w3d/component/MainManager.h"
#include "components/TransformCmpt.h"
#include "components/CubeCmpt.h"
#include "components/BackAndForthCmpt.h"
#include "components/LimitedLifeSpanCmpt.h"


#include <random>

W3D::Math::fVec3 randOnSphere(float radius, std::default_random_engine* generator, std::uniform_real_distribution<float>* distribution);

int main()
{
	W3D::Graphics::GLFW::init();
	
	W3D::Graphics::Window window(1280, 720, "Tremor");
	window.makeCurrentContext();


	gladLoadGL();
	glViewport(0, 0, 1280, 720);
	glEnable(GL_DEPTH_TEST);

	W3D::Graphics::Texture t("resources/textures/Shadowfell.jpg");

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

	W3D::Graphics::Shader shader(vertexShaderSource, fragmentShaderSource);

	std::default_random_engine generator;
	std::uniform_real_distribution<float> distribution(0.0f, 1.0f);
	std::uniform_real_distribution<float> distribution2(10.0f, 15.0f);


	W3D::Components::MainManager mm;

	float radius = 2;
	//set up scene
	for(int i = 0; i < 1000; i++)
	{
		W3D::Components::Entity* e = mm.getEManager()->makeEntity();
		TransformCmpt* transform = mm.getCManager()->makeComponent<TransformCmpt>(e);
		CubeCmpt* cube = mm.getCManager()->makeComponent<CubeCmpt>(e);
		BAFCmpt* baf = mm.getCManager()->makeComponent<BAFCmpt>(e);
		LimitedLifeSpaceCmpt* lifeSpan = mm.getCManager()->makeComponent<LimitedLifeSpaceCmpt>(e);


		cube->shader = &shader;

		W3D::Math::fVec3 posA = randOnSphere(radius, &generator, &distribution);
		W3D::Math::fVec3 posB = randOnSphere(radius, &generator, &distribution);

		
		baf->pathStart = posA;
		baf->pathEnd = posB;
		baf->pathLengthTime = 2.0f;
		
		//transform->position = posA;
		transform->scale = W3D::Math::fVec3::One() * (distribution(generator) * 0.1f);

		//random number between 5 and 15
		lifeSpan->time = distribution2(generator);

	}


	mm.update();

	printf("Num Entities: %i\n", mm.getEManager()->numEntities());

	shader.use();
	
	W3D::Math::Transform proj = W3D::Math::Transform::Identity() * W3D::Math::Transform::Perspective(45.0f, 1280.0f / 720.0f, 0.1f, 100.0f);
	shader.setMatrix("projection", proj);


	while (!window.shouldClose())
	{
		glClearColor(0.0, 0.0, 0.0, 1.0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


		const float radius = 10.0f;
		float camX = sin(W3D::Graphics::GLFW::getTime()) * radius;
		float camZ = cos(W3D::Graphics::GLFW::getTime()) * radius;
		W3D::Math::Transform view = W3D::Math::Transform::Identity() * W3D::Math::Transform::Translate(W3D::Math::fVec3(0.0f, 0.0f, -5.0f));
		//Transform view = Transform::LookAt(fVec3(camX, 0.0f, camZ), fVec3(), fVec3(0.0f, 1.0f, 0.0f));

		shader.setMatrix("view", view);


		t.bind();
		mm.update();


		W3D::Graphics::GLFW::pollEvents();
		window.swapBuffers();
	}

	return 0;
}

W3D::Math::fVec3 randOnSphere(float radius, std::default_random_engine* generator, std::uniform_real_distribution<float>* distribution)
{
	float u = distribution->operator()(*generator);
	float v = distribution->operator()(*generator);

	float theta = 2 * 3.14159f * u;
	float phi = std::acosf(2 * v - 1);
	W3D::Math::fVec3 pos;
	pos.x = radius * std::sin(phi) * std::cos(theta);
	pos.y = radius * std::sin(phi) * std::sin(theta);
	pos.z = radius * std::cos(phi);

	return pos;
}
