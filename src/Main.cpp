#include <glad/glad.h>

#include "w3d/math/fVec3.h"
#include "w3d/graphics/GLFW.h"
#include "w3d/graphics/Window.h"
#include "w3d/graphics/Shader.h"
#include "w3d/graphics/Camera.h"
#include "w3d/graphics/Mesh.h"
#include <w3d/graphics/Renderer.h>

#include "w3d/input/Input.h"

#include "w3d/util/Time.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "w3d/component/MainManager.h"

#include "components/TransformCmpt.h"
#include "components/CameraControllerCmpt.h"
#include "components/ModelCmpt.h"
#include "components/PlayerControllerCmpt.h"
#include "components/RotateCmpt.h"

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

	const char* vertexShaderSource = R"(
	#version 330 core
	layout(location = 0) in vec3 aPos;
	layout(location = 1) in vec3 aNormal;
	layout(location = 2) in vec2 aTexCoord;
	out vec2 TexCoord;
	uniform mat4 object;
	uniform mat4 view;
	uniform mat4 projection;
	uniform mat4 model;
	void main()
	{
		gl_Position = projection * view * object * model * vec4(aPos, 1.0);
		TexCoord = aTexCoord;
	})";

	const char* fragmentShaderSource = R"(
	#version 330 core
	out vec4 FragColor;
	in vec2 TexCoord;
	uniform sampler2D texture_diffuse1;
	void main()
	{
		FragColor = texture(texture_diffuse1, TexCoord);
	})";

	W3D::Graphics::Shader shader(vertexShaderSource, fragmentShaderSource);
	
	W3D::Input::Keyboard::Monitor(&window);

	W3D::Input::Keyboard::addInput("forward",	W3D::Input::Keycode::W);
	W3D::Input::Keyboard::addInput("left",		W3D::Input::Keycode::A);
	W3D::Input::Keyboard::addInput("backward",	W3D::Input::Keycode::S);
	W3D::Input::Keyboard::addInput("right",		W3D::Input::Keycode::D);
	W3D::Input::Keyboard::addInput("jump",		W3D::Input::Keycode::Spacebar);
	W3D::Input::Keyboard::addInput("crouch",	W3D::Input::Keycode::Left_Shift);


	W3D::Input::Keyboard::addInput("lookLeft",	W3D::Input::Keycode::Left);
	W3D::Input::Keyboard::addInput("lookRight",	W3D::Input::Keycode::Right);
	W3D::Input::Keyboard::addInput("lookUp",	W3D::Input::Keycode::Up);
	W3D::Input::Keyboard::addInput("lookDown",	W3D::Input::Keycode::Down);



	glm::mat4 myMatrix;
	glm::vec4 myVector;
	// fill myMatrix and myVector somehow
	glm::vec4 transformedVector = myMatrix * myVector; // Again, in this order ! this is important.


	W3D::Graphics::Camera camera;
	W3D::Graphics::Renderer::setCamera(&camera);
	//camera.position = W3D::Math::fVec3(0.0f, 0.0f, -5.0f);



	W3D::Graphics::Model model("resources/assets/orc/Medival Orc Character.obj");

	W3D::Components::MainManager mm;
	//set up scene
	{
		W3D::Components::Entity* camE = mm.getEManager()->makeEntity();
		TransformCmpt* transform = mm.getCManager()->makeComponent<TransformCmpt>(camE);
		CameraControllerCmpt* cc = mm.getCManager()->makeComponent<CameraControllerCmpt>(camE);

		PlayerControllerCmpt* playerC = mm.getCManager()->makeComponent<PlayerControllerCmpt>(camE);

		cc->camera = &camera;
		//raise eye height by 1.68m
		//transform->position += W3D::Math::fVec3(0.0f, 1.68f, 0.0f);
	}

	{
		W3D::Components::Entity* orc = mm.getEManager()->makeEntity();
		TransformCmpt* transform = mm.getCManager()->makeComponent<TransformCmpt>(orc);
		ModelCmpt* orcModel = mm.getCManager()->makeComponent<ModelCmpt>(orc);
		RotateCmpt* rot = mm.getCManager()->makeComponent<RotateCmpt>(orc);

		transform->position.z = -5;
		transform->position.y = 1.68;

		transform->rotation.rotateAround(transform->Left(), 90);

		orcModel->model = &model;
		orcModel->shader = &shader;
	}

	{
		W3D::Components::Entity* orc = mm.getEManager()->makeEntity();
		TransformCmpt* transform = mm.getCManager()->makeComponent<TransformCmpt>(orc);
		ModelCmpt* orcModel = mm.getCManager()->makeComponent<ModelCmpt>(orc);
		RotateCmpt* rot = mm.getCManager()->makeComponent<RotateCmpt>(orc);

		transform->position.x = -5;
		transform->position.y = 1.68;

		orcModel->model = &model;
		orcModel->shader = &shader;
	}

	{
		W3D::Components::Entity* orc = mm.getEManager()->makeEntity();
		TransformCmpt* transform = mm.getCManager()->makeComponent<TransformCmpt>(orc);
		ModelCmpt* orcModel = mm.getCManager()->makeComponent<ModelCmpt>(orc);
		RotateCmpt* rot = mm.getCManager()->makeComponent<RotateCmpt>(orc);

		transform->position.x = 5;
		transform->position.y = 1.68;

		orcModel->model = &model;
		orcModel->shader = &shader;
	}


	{
		W3D::Components::Entity* orc = mm.getEManager()->makeEntity();
		TransformCmpt* transform = mm.getCManager()->makeComponent<TransformCmpt>(orc);
		ModelCmpt* orcModel = mm.getCManager()->makeComponent<ModelCmpt>(orc);
		RotateCmpt* rot = mm.getCManager()->makeComponent<RotateCmpt>(orc);

		transform->position.z = 5;
		//transform->position.y = 1.68;

		//rot->turnRate = -rot->turnRate;

		orcModel->model = &model;
		orcModel->shader = &shader;
	}


	mm.update();

	printf("Num Entities: %i\n", mm.getEManager()->numEntities());

	shader.use();
	
	W3D::Math::Mat4 proj = W3D::Math::Mat4::Identity() * W3D::Math::Mat4::Perspective(45.0f, 1280.0f / 720.0f, 0.1f, 100.0f) *
		W3D::Math::Mat4::Scale(W3D::Math::fVec3(1.0, -1.0, 1.0));
	shader.setMatrix("projection", proj);

	float time = 0.0;

	while (!window.shouldClose())
	{
		glClearColor(0.0, 0.0, 0.0, 1.0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//one rotation every 5 seconds
		//camera.eulerAngles.y += W3D::Time::DTime() * 3.14159f * 0.4f;


		const float radius = 10.0f;
		float camX = sin(time) * radius;
		float camZ = cos(time) * radius;
		
		//glm::lookAt

		mm.update();

		time += W3D::Time::DTime();


		W3D::Time::update();
		W3D::Input::Keyboard::update();
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
