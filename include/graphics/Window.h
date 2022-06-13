#pragma once

struct GLFWwindow;
namespace W3D::Graphics
{

	class Window
	{
	public:

		Window(int width, int height, const char* name);

		void makeCurrentContext();

		void swapBuffers();

		bool shouldClose();


	private:
		struct glfwWindowUserInfo
		{
			Window* window;
		};

		GLFWwindow* pWindow;
		glfwWindowUserInfo userInfo;
	};

}