#include "w3d/input/Input.h"
#include "w3d/graphics/Window.h"
#include <GLFW/glfw3.h>
#include <unordered_map>

namespace W3D::Input
{
	//maps the input name to its value
	std::unordered_map<std::string, InputState> inputValues;
	//maps the keycode to its input name, if it has one
	std::unordered_map<Keycode, std::string> inputNameMap;


	void key_callback(int key, int scancode, int action, int mods)
	{
		Keycode kc = static_cast<Keycode> (key);

		auto f = inputNameMap.find(kc);
		//keycode doesnt have an alias
		if (f == inputNameMap.end()) return;

		auto f1 = inputValues.find(f->second);
		// name associated with keycode doesnt have a value. shouldnt happen
		if (f1 == inputValues.end()) return;


		InputState is = f1->second;

		if (action == GLFW_PRESS)
		{
			if (is == InputState::Free)				f1->second = InputState::Pressed;
			else if (is == InputState::Released)	f1->second = InputState::Pressed;
			else f1->second = InputState::Held;
		}

		if (action == GLFW_RELEASE)
		{
			if (is == InputState::Held)				f1->second = InputState::Released;
			else if (is == InputState::Pressed)		f1->second = InputState::Released;
			else f1->second = InputState::Free;
		}
	}

	void Keyboard::Monitor(W3D::Graphics::Window* window)
	{
		window->setKeyboardCallback(key_callback);
	}

	void Keyboard::addInput(std::string inputName, Keycode key)
	{
		inputNameMap.insert(std::make_pair(key, inputName));
		inputValues.insert(std::make_pair(inputName, InputState::Free));
	}

	InputState Keyboard::getInput(std::string input)
	{
		auto f = inputValues.find(input);
		//input name exists
		if (f != inputValues.end())
		{
			return f->second;
		}
		else
		{
			return InputState::Free;
		}
	}

	bool Keyboard::isInputDown(std::string input)
	{
		auto f = inputValues.find(input);
		//input name exists
		if (f != inputValues.end())
		{
			InputState is = f->second;
			if (is == InputState::Pressed || is == InputState::Held)
			{
				return true;
			}
			else
			{
				return false;
			}
		}
		else
		{
			return false;
		}
	}

	void Keyboard::update()
	{
		for (auto& p : inputValues)
		{
			if (p.second == InputState::Pressed) p.second = InputState::Held;
			if (p.second == InputState::Released) p.second = InputState::Free;
		}
	}

}