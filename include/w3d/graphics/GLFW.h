#pragma once

namespace W3D::Graphics
{
	class Window;
	namespace GLFW
	{
		int init();

		void cleanUp();

		void pollEvents();

		float getTime();
	}
}