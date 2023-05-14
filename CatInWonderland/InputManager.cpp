#define _CRT_SECURE_NO_WARNINGS

#include <cassert>
#include <Windows.h>
#include <stdio.h>

#include "InputManager.h"
#include "WinApp.h"

namespace catInWonderland
{
	InputManager* InputManager::mInstance = nullptr;

	InputManager* InputManager::GetInstance()
	{
		if (mInstance == nullptr)
		{
			mInstance = new InputManager();
			mInstance->Reset();
		}

		return mInstance;
	}

	void InputManager::DeleteInstance()
	{
		delete mInstance;
		mInstance = nullptr;
	}

	void InputManager::Reset()
	{
		mMousePos = { 0, 0 };
		memset(mKeyState, static_cast<int>(eKeyState::NONE), KEY_SIZE * sizeof(eKeyState));
	}

	void InputManager::Frame()
	{
		POINT curMousePos;
		GetCursorPos(&curMousePos); // temp
		if (ScreenToClient(WinApp::GetHWND(), &curMousePos) != false)
		{
			mMousePos = curMousePos;
		}

		if (mKeyState[VK_LBUTTON] != eKeyState::NONE)
		{
			char buffer[64];
			sprintf(buffer, "x : %d / y : %d\n", mMousePos.x, mMousePos.y);
			// OutputDebugStringA(buffer);
		}

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
