#include "w3d/graphics/Window.h"
#include <GLFW/glfw3.h>




namespace W3D::Graphics
{

	Window* getFromUserData(void* p)
	{
		Window::glfwWindowUserInfo* userInfo = (Window::glfwWindowUserInfo*)(p);

		if (userInfo == nullptr) return nullptr;
		else return userInfo->window;
	}

	void key_callback(GLFWwindow* win, int key, int scancode, int action, int mods)
	{
		Window* window = getFromUserData(glfwGetWindowUserPointer(win));

		if (window->keyboardCallback != nullptr)
		{
			window->keyboardCallback(key, scancode, action, mods);
		}
	}


	Window::Window(int width, int height, const char* name)
	{
		//create window
		pWindow = glfwCreateWindow(width, height, name, nullptr, nullptr);

		//set user pointer
		userInfo.window = this;
		glfwSetWindowUserPointer(pWindow, (void*)&userInfo);

		mouseCallback = nullptr;
		keyboardCallback = nullptr;
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

	void Window::setMouseCallback(MouseCallback mcb)
	{
		//resetting callback
		if (mcb == nullptr)
		{

		}
	}

	void Window::setKeyboardCallback(KeyboardCallback kbcb)
	{
		keyboardCallback = kbcb;
		//resetting callback
		if (kbcb == nullptr)
		{
			glfwSetKeyCallback(pWindow, NULL);
		}
		else
		{
			glfwSetKeyCallback(pWindow, key_callback);
		}
	}
}