#include <glad/glad.h>
#include <GLFW/glfw3.h>


int main()
{
	glfwInit();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

	GLFWwindow* window = glfwCreateWindow(1280, 720, "Tremor", nullptr, nullptr);
	glfwMakeContextCurrent(window);

	gladLoadGL();
	glViewport(0, 0, 1280, 720);

	glClearColor(0.0, 0.0, 0.0, 1.0);

	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();
		glClear(GL_COLOR_BUFFER_BIT);



	}

	glfwTerminate();
	return 0;
}