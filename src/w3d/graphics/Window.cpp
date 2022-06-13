#include "w3d/graphics/Window.h"
#include <GLFW/glfw3.h>

namespace W3D::Graphics
{

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
	bool Window::isFocused()
	{
		return (glfwGetWindowAttrib(pWindow, GLFW_FOCUSED) == GL_TRUE);
	}
}