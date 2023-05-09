#include "Player.h"
#include "InputManager.h"
#include "TimeManager.h"
#include "RenderManager.h"
#include "PlayerIdle.h"

namespace hockman
{
	Player::Player(hRectangle rectangle, eSpriteType spriteType, eObjectType objectType, float moveSpeed)
		: Object(rectangle, spriteType, objectType)
		, mMoveSpeed(moveSpeed)
		, mPlayerState(new PlayerIdle())
	{
	}

	void Player::Frame()
	{
		const float DELTA_TIME = TimeManager::GetInstance()->GetDeltaTime();


		switch (mState)
		{
		case ePlayerState::Idle:
		{
			if (InputManager::GetInstance()->GetKeyState(VK_LEFT) == eKeyState::PUSH)		
			{
				// run���� ���� ����
			}
			else if (InputManager::GetInstance()->GetKeyState(VK_RIGHT) == eKeyState::PUSH)
			{
				// run���� ���� ����
			}
			else if (InputManager::GetInstance()->GetKeyState(VK_SPACE) == eKeyState::PUSH)
			{
				// ������ ���� ����
			}
		}
		break;
		case ePlayerState::Run:
		{
			if (InputManager::GetInstance()->GetKeyState(VK_LEFT) == eKeyState::NONE
				&& InputManager::GetInstance()->GetKeyState(VK_RIGHT) == eKeyState::NONE)
			{
				// idle�� ���� ����
			}

			if (InputManager::GetInstance()->GetKeyState(VK_SPACE) == eKeyState::PUSH)
			{
				// ������ ���� ����
			}
		}
		break;
		case ePlayerState::Jump:
		{
			// if (���� ������)
			{
				if (InputManager::GetInstance()->GetKeyState(VK_LEFT) != eKeyState::NONE)
				{
					// run���� ���� ����
				}
				else if(InputManager::GetInstance()->GetKeyState(VK_RIGHT) != eKeyState::NONE)
				{
					// run�� ���� ����
				}
				else
				{
					// idle�� ���� ����
				}
			}
		}
		break;
		}

		const Vector2& pos = mRectangle.GetPos();

		if (InputManager::GetInstance()->GetKeyState(VK_LEFT) == eKeyState::HOLD)
		{
			mRectangle.SetPos(pos.GetX() - mMoveSpeed * DELTA_TIME, pos.GetY());
		}
		if (InputManager::GetInstance()->GetKeyState(VK_RIGHT) == eKeyState::HOLD)
		{
			mRectangle.SetPos(pos.GetX() + mMoveSpeed * DELTA_TIME, pos.GetY());
		}
		if (InputManager::GetInstance()->GetKeyState(VK_DOWN) == eKeyState::HOLD)
		{
			mRectangle.SetPos(pos.GetX(), pos.GetY() + mMoveSpeed * DELTA_TIME);
		}
		if (InputManager::GetInstance()->GetKeyState(VK_UP) == eKeyState::HOLD)
		{
			mRectangle.SetPos(pos.GetX(), pos.GetY() - mMoveSpeed * DELTA_TIME);
		}

		if (mCanJump && InputManager::GetInstance()->GetKeyState(VK_SPACE) == eKeyState::PUSH)
		{
			mState = ePlayerState::Jump;
			mCanJump = false;

		}
	}

	void Player::Render()
	{
		RenderManager::GetInstance()->DrawRect(mRectangle, RGB(0, 255, 0));
	}
}