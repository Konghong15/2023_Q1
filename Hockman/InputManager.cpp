#define _CRT_SECURE_NO_WARNINGS

#include <cassert>
#include <Windows.h>
#include <stdio.h>

#include "InputManager.h"
#include "RenderManager.h"

namespace hockman
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
		: mKeyState{ eKeyState::NONE, }
	{
	}

	void InputManager::Frame()
	{
		GetCursorPos(&mMousePos);
		COORD screenPos = RenderManager::GetInstance()->GetScreenInfo().dwCursorPosition;

		mMousePos.x -= screenPos.X;
		mMousePos.y -= screenPos.Y;

		if (mKeyState[VK_LBUTTON] != eKeyState::NONE)
		{
			char buffer[64];
			sprintf(buffer, "x : %d / y : %d\n", mMousePos.x, mMousePos.y);
			OutputDebugStringA(buffer);
		}

		//HWND hWnd = WindowFromPoint(mMousePos); // temp
		//ScreenToClient(hWnd, &mMousePos);

		for (int i = 0; i < KEY_SIZE; ++i)
		{
			if (GetAsyncKeyState(i) & 0x8000)
			{
				switch (mKeyState[i])
				{
				case eKeyState::NONE:
					/* intentional  fall-through */
				case eKeyState::POP:
					mKeyState[i] = eKeyState::PUSH;
					break;
				case eKeyState::PUSH:
					/* intentional  fall-through */
				case eKeyState::HOLD:
					mKeyState[i] = eKeyState::HOLD;
					break;
				default:
					assert(false);
					break;
				}
			}
			else
			{
				switch (mKeyState[i])
				{
				case eKeyState::NONE:
					/* intentional  fall-through */
				case eKeyState::POP:
					mKeyState[i] = eKeyState::NONE;
					break;
				case eKeyState::PUSH:
					/* intentional  fall-through */
				case eKeyState::HOLD:
					mKeyState[i] = eKeyState::POP;
					break;
				default:
					assert(false);
					break;
				}
			}
		}
	}
};
