#pragma once

#include "Player.h"
#include "InputManager.h"
#include "TimeManager.h"

namespace hongpireSurvivors
{
	Player::Player(COORD pos, COORD size, eSpriteType spriteType)
		: Object(pos, size, spriteType)
		, mCanMove(true)
		, mElapsed(0.f)
	{
	}

	void Player::Frame()
	{
		if (!mCanMove)
		{
			mElapsed += TimeManager::GetInstance()->GetDeltaTime();

			if (mElapsed >= 1.0f)
			{
				mElapsed = 0.0f;
				mCanMove = true;
			}

			return;
		}


		if (InputManager::GetInstance()->GetKeyState(VK_LEFT) != eKeyState::NONE)
		{
			--mPos.X;
		}
		else if (InputManager::GetInstance()->GetKeyState(VK_RIGHT) != eKeyState::NONE)
		{
			++mPos.X;
		}
		else if (InputManager::GetInstance()->GetKeyState(VK_UP) != eKeyState::NONE)
		{
			--mPos.Y;
		}
		else if (InputManager::GetInstance()->GetKeyState(VK_DOWN) != eKeyState::NONE)
		{
			++mPos.Y;
		}

		mCanMove = false;
	}
}