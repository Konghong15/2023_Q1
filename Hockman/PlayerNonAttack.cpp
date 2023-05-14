#pragma once

#include "PlayerNonAttack.h"
#include "InputManager.h"
#include "TimeManager.h"
#include "PlayerAttack.h"
#include "PlayerCharging.h"

namespace hockman
{
	PlayerNonAttack::PlayerNonAttack()
		: PlayerState(ePlayerState::NonAttack)
		, mKeyElapsedTime(0.f)
	{
	}

	void PlayerNonAttack::Enter(Player* player)
	{

	}

	PlayerState* PlayerNonAttack::HandleInputOrNull(Player* player)
	{
		if (mKeyElapsedTime > 0.2f)
		{
			return new PlayerCharging();
		}

		if (InputManager::GetInstance()->GetKeyState('X') == eKeyState::POP)
		{
			return new PlayerAttack();
		}

		return nullptr;
	}

	void PlayerNonAttack::Update(Player* player)
	{
		const float DELTA_TIME = TimeManager::GetInstance()->GetDeltaTime();

		if (InputManager::GetInstance()->GetKeyState('X') == eKeyState::PUSH
			|| InputManager::GetInstance()->GetKeyState('X') == eKeyState::HOLD)
		{
			mKeyElapsedTime += DELTA_TIME;
		}
	}
}