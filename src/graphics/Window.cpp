#include "graphics/Window.h"
#include <GLFW/glfw3.h>

Window::Window(int width, int height, const char* name)
{
	//create window
	pWindow = glfwCreateWindow(width, height, name, nullptr, nullptr);

	//set user pointer
	userInfo.window = this;
	glfwSetWindowUserPointer(pWindow, (void*)&userInfo);
}

void Window::makeCurrentContext()
{
	glfwMakeContextCurrent(pWindow);
}

void Window::swapBuffers()
{
	glfwSwapBuffers(pWindow);
}

bool Window::shouldClose()
{
	return glfwWindowShouldClose(pWindow);
}
