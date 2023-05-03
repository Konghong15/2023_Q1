#include "Player.h"
#include "InputManager.h"
#include "TimeManager.h"
#include "RenderManager.h"

namespace hockman
{
	Player::Player(Vector2 pos, Vector2 size, Vector2 direction, eSpriteType spriteType, eObjectType objectType, float moveSpeed)
		: Object(pos, size, direction, spriteType, objectType)
		, mMoveSpeed(moveSpeed)
	{
	}

	void Player::Frame()
	{
		const float DELTA_TIME = TimeManager::GetInstance()->GetDeltaTime();

		if (InputManager::GetInstance()->GetKeyState(VK_LEFT) == eKeyState::HOLD)
		{
			mPos.SetX(mPos.GetX() - mMoveSpeed * DELTA_TIME);
		}
		if (InputManager::GetInstance()->GetKeyState(VK_RIGHT) == eKeyState::HOLD)
		{
			mPos.SetX(mPos.GetX() + mMoveSpeed * DELTA_TIME);
		}
		if (InputManager::GetInstance()->GetKeyState(VK_DOWN) == eKeyState::HOLD)
		{
			mPos.SetY(mPos.GetY() + mMoveSpeed * DELTA_TIME);
		}
		if (InputManager::GetInstance()->GetKeyState(VK_UP) == eKeyState::HOLD)
		{
			mPos.SetY(mPos.GetY() - mMoveSpeed * DELTA_TIME);
		}
	}

	void Player::Render()
	{
		RenderManager::GetInstance()->DrawRect(mPos.GetX(), mPos.GetY(), mSize.GetX(), mSize.GetY(), RGB(0, 255, 0));
	}
}