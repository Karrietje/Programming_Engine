#pragma once
#include <Windows.h>
#include <Xinput.h>
#include <map>
#include <memory>
#include "Singleton.h"

class Command;
namespace dae
{
	enum class InputType
	{
		KeyDown,
		KeyUp,
		KeyHold
	};

	struct ControllerInput
	{
		//Which key 
		int input;
		InputType inputType;

		bool operator<(const ControllerInput& other) const
		{
			return input < other.input;
		}
	};

	class InputManager final : public Singleton<InputManager>
	{
	public:
		~InputManager();
		bool ProcessInput();
		void AddCommand(ControllerInput input, Command* command);

	private:
		XINPUT_KEYSTROKE m_ControllerState;
		std::map<ControllerInput, Command*> m_pControllerCommands;
	};
}

