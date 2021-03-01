#include "MiniginPCH.h"
#include "InputManager.h"
#include <SDL.h>
#include "Command.h"


bool dae::InputManager::ProcessInput()
{
	//Wat in m_ControllerState zit leegmaken =>De grootte van input_State
	ZeroMemory(&m_ControllerState, sizeof(XINPUT_KEYSTROKE));
	XInputGetKeystroke(0, 0, &m_ControllerState);

	SDL_Event e;
	while (SDL_PollEvent(&e)) {
		if (e.type == SDL_QUIT) {
			return false;
		}
		if (e.type == SDL_KEYDOWN) {
			
		}
		if (e.type == SDL_MOUSEBUTTONDOWN) {
			
		}
	}

	for (std::pair<ControllerInput, std::shared_ptr<Command>> command : m_pControllerCommands)
	{
		if (command.first.input == m_ControllerState.VirtualKey)
		{
			switch (command.first.inputType)
			{
			case InputType::KeyDown:
				if (m_ControllerState.Flags & XINPUT_KEYSTROKE_KEYDOWN)
					command.second->Execute();
				break;
			case InputType::KeyHold:
				if (m_ControllerState.Flags & XINPUT_KEYSTROKE_REPEAT)
					command.second->Execute();
				break;
			case InputType::KeyUp:
				if (m_ControllerState.Flags & XINPUT_KEYSTROKE_KEYUP)
					command.second->Execute();
				break;
			default:
				break;
			}
		}
	}
	return true;
}

void dae::InputManager::AddCommand(ControllerInput input, const std::shared_ptr<Command>& command)
{
	m_pControllerCommands[input] = command;
}
