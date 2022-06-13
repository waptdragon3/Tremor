#pragma once
#include "w3d/math/fVec3.h"


struct GLFWwindow;

namespace W3D::Graphics
{
	using MouseCallback = void (*) (W3D::Math::fVec3 pos);
	using KeyboardCallback = void (*) (int key, int scancode, int action, int mods);

	class Window
	{
	public:

		Window(int width, int height, const char* name);

		void makeCurrentContext();
		void swapBuffers();
		bool shouldClose();
		bool isFocused();

		void setMouseCallback(MouseCallback mcb);
		void setKeyboardCallback(KeyboardCallback kbcb);

	private:
		struct glfwWindowUserInfo
		{
			Window* window;
		};

		GLFWwindow* pWindow;
		glfwWindowUserInfo userInfo;
		
		MouseCallback mouseCallback;
		KeyboardCallback keyboardCallback;

		friend Window* getFromUserData(void* p);
		friend void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

	};

}