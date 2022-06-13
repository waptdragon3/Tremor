#pragma once
#include "w3d/math/fVec3.h"

struct GLFWwindow;

namespace W3D::Graphics
{
	using MouseCallback = void (*) (W3D::Math::fVec3 pos);
	class Window
	{
	public:

		Window(int width, int height, const char* name);

		void makeCurrentContext();
		void swapBuffers();
		bool shouldClose();
		bool isFocused();

		void setMouseCallback(MouseCallback mcb);

	private:
		struct glfwWindowUserInfo
		{
			Window* window;
		};

		GLFWwindow* pWindow;
		glfwWindowUserInfo userInfo;
		MouseCallback mouseCallback;
	};

}