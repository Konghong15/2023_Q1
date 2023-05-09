#include "PlayerIdle.h"
#include "PlayerJump.h"
#include "PlayerRun.h"
#include "Player.h"
#include "InputManager.h"
#include "TimeManager.h"

namespace hockman
{
	PlayerJump::PlayerJump()
		: PlayerState(ePlayerState::Jump)
	{
	}

	void PlayerJump::Enter(Player* player)
	{
		player->SetAniElapsed(0.f);
		player->SetAniDuration(0.2f);
		player->SetIsAniLoop(true);
		player->SetUVRectangles(&mJumpUVRects);
	}

	PlayerState* PlayerJump::HandleInputOrNull(Player* player)
	{
		return nullptr;
	}

	void PlayerJump::Update(Player* player)
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