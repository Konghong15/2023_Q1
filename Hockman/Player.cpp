#include "Player.h"
#include "InputManager.h"
#include "TimeManager.h"
#include "RenderManager.h"
#include "PlayerIdle.h"
#include "PlayerNonAttack.h"
#include "Collider.h"

namespace hockman
{
	Player::Player(hRectangle rectangle, hRectangle uvRectangle, eSpriteType spriteType, eObjectType objectType, float moveSpeed)
		: Object(rectangle, spriteType, objectType)
		, mUVRectangle(uvRectangle)
		, mMoveSpeed(moveSpeed)
		, mPlayerState(new PlayerIdle())
		, mPlayerAttackState(new PlayerNonAttack())
		, mIsRight(true)
		, mGravity(5000.f)
		, mAniIndexY(0)
	{
		mPlayerState->Enter(this);
		mPlayerAttackState->Enter(this);
	}

	void Player::Frame()
	{
		const float DELTA_TIME = TimeManager::GetInstance()->GetDeltaTime();

		mPlayerState->Update(this);
		PlayerState* nextState = mPlayerState->HandleInputOrNull(this);

		if (nextState != nullptr)
		{
			delete mPlayerState;
			mPlayerState = nextState;
			nextState->Enter(this);
		}

		mPlayerAttackState->Update(this);
		PlayerState* nextAttackState = mPlayerAttackState->HandleInputOrNull(this);

		if (nextAttackState != nullptr)
		{
			delete mPlayerAttackState;
			mPlayerAttackState = nextAttackState;
			nextAttackState->Enter(this);
		}
	}

	void Player::Render()
	{
		hRectangle anlRect = mUVRectangles->at(mAniIndex);
		anlRect.SetPos(anlRect.GetPos().GetX(), anlRect.GetPos().GetY() + mAniIndexY * 32);

		RenderManager::GetInstance()->Draw(mSpriteType, mRectangle, anlRect, mIsRight);
	}
}