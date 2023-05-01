#include <cassert>
#include <time.h>

#include "Devil.h"
#include "TimeManager.h"
#include "EnemyProjectile.h"
#include "ObjectManager.h"
#include "Helper.h"
#include "Scene.h"

namespace hongpireSurvivors
{
	Devil::Devil(COORD pos, COORD size, int minX, int maxX, bool isLeft)
		: Monster(pos, size, eSpriteType::ENEMY_1, minX, maxX, 3, isLeft)
		, mAttackElapsed(0.f)
		, mCanAttack(false)
		, mStartPos(pos)
		, mMoveCount(0)
		, mDevildState(eDevilState::MOVE)
		, mMaxElapsed(0.f)
	{
		if (isLeft)
		{
			mArrivalPos = { (SHORT)(pos.X - rand() % 300), 5 };
		}
		else
		{
			mArrivalPos = { (SHORT)(pos.X + rand() % 300), 5 };
		}
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
		if (mElapsed < ONE_FRAME_TIME)
		{
			return;
		}

		mElapsed -= ONE_FRAME_TIME;

		int increaseX = mArrivalPos.X - mPos.X;
		int increaseY = mArrivalPos.Y - mPos.Y;

		int xAmonut = 0;
		int yAmount = 0;
		const int SPEED = mDevildState == eDevilState::CLOSE_RANGE_ATTACK ? MONSTER_SPEED_HIGH : MONSTER_SPEED_MIDDLE;

		if (increaseX == 0)
		{
			yAmount = SPEED;
		}
		else if (increaseY == 0)
		{
			xAmonut = SPEED;
		}
		else
		{
			assert(increaseY != 0);

			float slope = increaseY / (float)increaseX;

			if (fabs(slope) < 1.f)
			{
				yAmount = static_cast<int>(slope * SPEED);
				xAmonut = SPEED;
			}
			else
			{
				yAmount = SPEED;
				xAmonut = static_cast<int>(SPEED / slope);
			}
		}

		if (mArrivalPos.X < mPos.X)
		{
			mPos.X = mPos.X - abs(xAmonut);

			if (mArrivalPos.Y < mPos.Y)
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

			const Object* player = ObjectManager::GetInstance()->GetPlayerOrNull();
			COORD playerPos = player->GetPos();
			EnemyProjectile* proj = new EnemyProjectile(playerPos, mPos, { 4, 4 }, eSpriteType::ENEMY_1_PROJECTILE, mMinX, mMaxX, mIsLeft);
			Helper::Spawn(proj, 4, 4);
		}
	}

	void Devil::handleState()
	{
		const Object* player = ObjectManager::GetInstance()->GetPlayerOrNull();
		COORD playerPos = player->GetPos();

		if (abs(mPos.X - mArrivalPos.X) < 4 && abs(mPos.Y - mArrivalPos.Y) < 4)
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

				mArrivalPos.X = Helper::Clamp(0, Helper::MAP_WIDTH - mSize.X, mArrivalPos.X);
				mArrivalPos.Y = Helper::Clamp(0, 67 - mSize.Y, mArrivalPos.Y);

				mStartPos = mPos;
				mMoveCount = 0;
				break;
			case eDevilState::CLOSE_RANGE_ATTACK:
			{
				mMaxElapsed = 0.015f;
				mDevildState = eDevilState::MOVE;
				if (mIsLeft)
				{
					mArrivalPos = { (SHORT)(mMaxX - rand() % 300), 5 };
				}
				else
				{
					mArrivalPos = { (SHORT)(mMinX + rand() % 300), 5 };
				}

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