#include "Orge.h"
#include "TimeManager.h"
#include "ObjectManager.h"
#include "Helper.h"

namespace hongpireSurvivors
{
	Orge::Orge(COORD pos, COORD size, bool isLeft)
		: Monster(pos, size, eSpriteType::BOSS_0_IDLE, isLeft)
		, mCanAttack(false)
		, mIsJump(false)
		, mDropElapsed(0.f)
		, mAttackElapsed(0.f)
		, mArrival(0)
	{
	}

	void Orge::Frame()
	{
		handleCollision();

		if (!mIsVaild)
		{
			return;
		}

		handleMove();
		handleAttack();
		handleJump();
	}

	void Orge::handleMove()
	{
		if (!mIsJump)
		{
			return;
		}
		if (mArrival == mPos.X)
		{
			return;
		}

		const float DELTA_TIME = TimeManager::GetInstance()->GetDeltaTime();
		mElapsed += DELTA_TIME;

		if (mElapsed >= 0.005f)
		{
			mElapsed -= 0.005f;
			mPos.X += mArrival > mPos.X ? 1 : -1;
		}
	}

	void Orge::handleJump()
	{
		if (!mIsJump)
		{
			return;
		}

		const float DELTA_TIME = TimeManager::GetInstance()->GetDeltaTime();
		mDropElapsed += DELTA_TIME;

		if (mDropElapsed >= 0.025f)
		{
			mDropElapsed -= 0.025f;


			if (mJumpForce > 0.25f)
			{
				mPos.Y -= 2;
				mPos.Y = Helper::Clamp(0, 67 - mSize.Y, mPos.Y);
				mSpriteType = eSpriteType::BOSS_0_JUMP;
			}
			else if (mJumpForce > 0.f)
			{
				mPos.Y -= 1;
			}
			else if (mJumpForce > -0.25f)
			{
				mPos.Y += 1;
			}
			else
			{
				mPos.Y += 2;
			}
		}

		mJumpForce -= DELTA_TIME * 1.5f;

		if (mPos.Y + mSize.Y > 67)
		{
			mSpriteType = eSpriteType::BOSS_0_IDLE;
			--mPos.Y;
			mIsJump = false;
			mJumpForce = 0.0f;
		}
	}

	void Orge::handleAttack()
	{
		if (mIsJump)
		{
			return;
		}


		const float DELTA_TIME = TimeManager::GetInstance()->GetDeltaTime();
		mAttackElapsed += DELTA_TIME;

		if (mAttackElapsed < 1.f)
		{
			return;
		}

		mAttackElapsed = 0.f;

		mArrival = ObjectManager::GetInstance()->GetPlayer().GetPos().X;
		mArrival = Helper::Clamp(0, 400 - 30, mArrival);
		mJumpForce = 0.75f;
		mIsJump = true;
		mIsLeft = mArrival > mPos.X ? false : true;
	}
}