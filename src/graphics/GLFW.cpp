#include "graphics/GLFW.h"
#include <GLFW/glfw3.h>

namespace W3D::Graphics
{

	int GLFW::init()
	{
		int x = glfwInit();

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);



		return x;
	}

	void GLFW::cleanUp()
	{
		glfwTerminate();
	}

	void GLFW::pollEvents()
	{
		glfwPollEvents();
	}

	float GLFW::getTime()
	{
		return static_cast<float>(glfwGetTime());
	}

}