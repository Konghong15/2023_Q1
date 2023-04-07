#include <cassert>
#include <time.h>

#include "Devil.h"
#include "TimeManager.h"
#include "EnemyProjectile.h"
#include "ObjectManager.h"
#include "Helper.h"

namespace hongpireSurvivors
{
	const COORD Devil::ORIJIN_LEFT{ 100, 20 };
	const COORD Devil::ORIJIN_RIGHT{ 300, 10 };

	Devil::Devil(COORD pos, COORD size, bool isLeft)
		: Monster(pos, size, eSpriteType::ENEMY_1, isLeft)
		, mAttackElapsed(0.f)
		, mCanAttack(false)
		, mStartPos(pos)
		, mArrivalPos(isLeft ? ORIJIN_LEFT : ORIJIN_RIGHT)
		, mMoveCount(0)
		, mDevildState(eDevilState::MOVE)
		, mSpeed(1u)
		, mMaxElapsed(0.02f)
	{
	}

	void Devil::Frame()
	{
		const float DELTA_TIME = TimeManager::GetInstance()->GetDeltaTime();
		mElapsed += DELTA_TIME;
		mAttackElapsed += DELTA_TIME;

		handleCollision();

		if (!mIsVaild)
		{
			return;
		}

		handleState();
		handleMove();
		handleAttack();
	}

	void Devil::handleMove()
	{
		if (mElapsed < mMaxElapsed)
		{
			return;
		}

		mElapsed -= mMaxElapsed;

		int increaseX = mArrivalPos.X - mPos.X;
		int increaseY = mArrivalPos.Y - mPos.Y;

		int xAmonut = 0;
		int yAmount = 0;

		if (increaseX == 0)
		{
			yAmount = 1;
		}
		else if (increaseY == 0)
		{
			xAmonut = 1;
		}
		else
		{
			assert(increaseY != 0);

			float slope = increaseY / (float)increaseX;

			if (fabs(slope) < 1.f)
			{
				yAmount = slope;
				xAmonut = 1;
			}
			else
			{
				yAmount = 1;
				xAmonut = 1 / slope;
			}
		}

		if (mArrivalPos.X < mPos.X)
		{
			mPos.X = mPos.X - abs(xAmonut);

			if (mArrivalPos.Y < mStartPos.Y)
			{
				mPos.Y = mPos.Y - abs(yAmount);
			}
			else
			{
				mPos.Y = mPos.Y + abs(yAmount);
			}
		}
		else
		{
			mPos.X = mPos.X + abs(xAmonut);

			if (mArrivalPos.Y < mPos.Y)
			{
				mPos.Y = mPos.Y - abs(yAmount);
			}
			else
			{
				mPos.Y = mPos.Y + abs(yAmount);
			}
		}
	}

	void Devil::handleAttack()
	{
		if (mAttackElapsed >= 1.5f && mDevildState == eDevilState::LONG_LRANGE_ATTACK)
		{
			mAttackElapsed = 0.f;

			const Object& player = ObjectManager::GetInstance()->GetPlayer();
			COORD playerPos = player.GetPos();
			EnemyProjectile* proj = new EnemyProjectile(player.GetPos(), mPos, { 4, 4 }, eSpriteType::ENEMY_1_PROJECTILE, mIsLeft);
			Helper::Spawn(proj, mPos.X, mPos.Y, 4, 4);
		}
	}

	void Devil::handleState()
	{
		const Object& player = ObjectManager::GetInstance()->GetPlayer();
		COORD playerPos = player.GetPos();

		if (mPos.X == mArrivalPos.X && mPos.Y == mArrivalPos.Y)
		{
			switch (mDevildState)
			{
			case eDevilState::MOVE:
				mDevildState = eDevilState::LONG_LRANGE_ATTACK;
				mIsLeft = mIsLeft ^ true;
				break;
			case eDevilState::LONG_LRANGE_ATTACK:
				mMaxElapsed = 0.01f;
				mDevildState = eDevilState::CLOSE_RANGE_ATTACK;
				mArrivalPos = playerPos;

				mArrivalPos.X = Helper::Clamp(0, 400 - mSize.X, mArrivalPos.X);
				mArrivalPos.Y = Helper::Clamp(0, 67 - mSize.Y, mArrivalPos.Y);

				mStartPos = mPos;
				mMoveCount = 0;
				break;
			case eDevilState::CLOSE_RANGE_ATTACK:
			{
				mMaxElapsed = 0.015f;
				mDevildState = eDevilState::MOVE;
				mArrivalPos = mIsLeft ? ORIJIN_LEFT : ORIJIN_RIGHT;

				int random = rand() % 50 - 25;
				mArrivalPos.X += random;
				random = rand() % 5;
				mArrivalPos.Y -= random;

				mStartPos = mPos;
				mMoveCount = 0;
			}
			break;
			default:
				assert(false);
				break;
			}
		}
	}
}