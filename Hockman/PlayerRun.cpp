#include "PlayerIdle.h"
#include "PlayerJump.h"
#include "PlayerRun.h"
#include "Player.h"
#include "InputManager.h"
#include "TimeManager.h"
#include "Collider.h"

namespace hockman
{
	PlayerRun::PlayerRun()
		: PlayerState(ePlayerState::Run)
	{
	}

	void PlayerRun::Enter(Player* player)
	{
		player->SetAniIndex(0);
		player->SetAniElapsed(0.f);
		player->SetAniDuration(0.2f);
		player->SetIsAniLoop(true);
		player->SetUVRectangles(&mRunUVRects);
		player->SetUVRectangles(&mRunUVRects);
		player->SetUVRectangles(&mRunUVRects);
	}

	PlayerState* PlayerRun::HandleInputOrNull(Player* player)
	{
		if (InputManager::GetInstance()->GetKeyState(VK_LEFT) == eKeyState::NONE
			&& InputManager::GetInstance()->GetKeyState(VK_RIGHT) == eKeyState::NONE)
		{
			return new PlayerIdle();
		}
		if (InputManager::GetInstance()->GetKeyState(VK_SPACE) != eKeyState::NONE)
		{
			return new PlayerJump();
		}

		return nullptr;
	}

	void PlayerRun::Update(Player* player)
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

		const float distanceX = player->GetMoveSpeed() * DELTA_TIME;
		if (InputManager::GetInstance()->GetKeyState(VK_LEFT) != eKeyState::NONE)
		{
			player->Move(-distanceX, 0);
			player->SetIsRight(false);
		}
		else if (InputManager::GetInstance()->GetKeyState(VK_RIGHT) != eKeyState::NONE)
		{
			player->Move(distanceX, 0);
			player->SetIsRight(true);
		}
	}
}