#include <cassert>
#include <Windows.h>

#include "InputManager.h"

namespace hongpireSurvivors
{
	InputManager* InputManager::mInstance = nullptr;

	InputManager* InputManager::GetInstance()
	{
		if (mInstance == nullptr)
		{
			mInstance = new InputManager();
		}

		return mInstance;
	}

	void InputManager::DeleteInstance()
	{
		delete mInstance;
		mInstance = nullptr;
	}

	InputManager::InputManager()
		: mkeyState{ eKeyState::NONE, }
	{
	}

	void InputManager::Frame()
	{
		for (int i = 0; i < KEY_SIZE; ++i)
		{
			if (GetAsyncKeyState(i) & 0x8000)
			{
				switch (mkeyState[i])
				{
				case eKeyState::NONE:
					/* intentional  fall-through */
				case eKeyState::POP:
					mkeyState[i] = eKeyState::PUSH;
					break;
				case eKeyState::PUSH:
					/* intentional  fall-through */
				case eKeyState::HOLD:
					mkeyState[i] = eKeyState::HOLD;
					break;
				default:
					assert(false);
					break;
				}
			}
			else
			{
				switch (mkeyState[i])
				{
				case eKeyState::NONE:
					/* intentional  fall-through */
				case eKeyState::POP:
					mkeyState[i] = eKeyState::NONE;
					break;
				case eKeyState::PUSH:
					/* intentional  fall-through */
				case eKeyState::HOLD:
					mkeyState[i] = eKeyState::POP;
					break;
				default:
					assert(false);
					break;
				}
			}
		}
	}
};
