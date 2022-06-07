#pragma once
class Window;
namespace GLFW
{
	int init();

	void cleanUp();

	void pollEvents();
}