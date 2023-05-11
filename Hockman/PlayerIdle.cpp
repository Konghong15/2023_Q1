#include "PlayerIdle.h"
#include "PlayerJump.h"
#include "PlayerRun.h"
#include "Player.h"
#include "TimeManager.h"
#include "InputManager.h"

namespace hockman
{
	PlayerIdle::PlayerIdle()
		: PlayerState(ePlayerState::Idle)
	{
	}

	void PlayerIdle::Enter(Player* player)
	{
		player->SetVX(0.f);
		player->SetVY(0.f);
		player->SetAniIndex(0);
		player->SetAniElapsed(0.f);
		player->SetAniDuration(1.f);
		player->SetIsAniLoop(true);
		player->SetUVRectangles(&mIdleUVRects);
	}

	PlayerState* PlayerIdle::HandleInputOrNull(Player* player)
	{
		if (InputManager::GetInstance()->GetKeyState(VK_LEFT) != eKeyState::NONE
			|| InputManager::GetInstance()->GetKeyState(VK_RIGHT) != eKeyState::NONE)
		{
			return new PlayerRun();
		}
		if (InputManager::GetInstance()->GetKeyState(VK_SPACE) != eKeyState::NONE)
		{
			return new PlayerJump();
		}

		return nullptr;
	}

	void PlayerIdle::Update(Player* player)
	{
		const float DELTA_TIME = TimeManager::GetInstance()->GetDeltaTime();

		player->AddAniElapsed(DELTA_TIME);

		const float ELAPSED = player->GetAniElapsed();
		const float DURATION = player->GetAniDuration();
		if (ELAPSED >= DURATION)
		{
			player->AddAniIndex();
			player->SetAniElapsed(ELAPSED - DURATION);
		}
	}
}