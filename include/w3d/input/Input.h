#pragma once
#include <string>

namespace W3D::Graphics
{
	class Window;
}

namespace W3D::Input
{
	//hardcoded values from https://www.glfw.org/docs/3.3/group__keys.html#gabf48fcc3afbe69349df432b470c96ef2
	enum class Keycode
	{
		Spacebar = 32,

		Key_0 = 48,	Key_1, Key_2, Key_3, Key_4, Key_5, Key_6, Key_7, Key_8, Key_9,

		Semicolon = 59, Equal = 61,
		
		A = 65,	B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V, W, X, Y, Z,
		
		LBracket = 91, Backslack, RBracket,
		
		Grave = 96, Escape = 256, Enter = 257, Tab = 258, Backspace = 259, Insert = 260, Delete = 261,

		Right = 262, Left, Down, Up,

		PageUp = 266, PageDown,

		Left_Shift = 340

	};

	/// <summary>
	/// The state of the input. when in the format 0bXY, x represents the previous frame and y is the current frame
	/// </summary>
	enum class InputState
	{
		// The input has been released for at least 2 frames
		Free = 0,
		// The input has just been pressed
		Pressed = 1,
		// The input has just been released
		Released = 2,
		// The input has been held down for at least 2 frames
		Held = 3
	};

	namespace Keyboard
	{
		void Monitor(W3D::Graphics::Window* window);

		void addInput(std::string inputName, Keycode key);
		InputState getInput(std::string input);
		bool isInputDown(std::string input);

		void update();
	}


	namespace Mouse
	{
		void Monitor(W3D::Graphics::Window* window);
	}
}