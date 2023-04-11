#include <cassert>

#include "FlyingOrge.h"
#include "ObjectManager.h"
#include "TimeManager.h"
#include "Helper.h"
#include "EnemyProjectile.h"
#include "Scene.h"

namespace hongpireSurvivors
{
	CONST COORD FlyingOrge::ORIJIN_LEFT_TOP{ 1220, 3 };
	CONST COORD FlyingOrge::ORIJIN_RIGHT_TOP{ 1550, 3 };
	CONST COORD FlyingOrge::ORIJIN_LEFT_BOTTOM{ 1220, 79 - 26 };
	CONST COORD FlyingOrge::ORIJIN_RIGHT_BOTTOM{ 1550, 79 - 26 };

	FlyingOrge::FlyingOrge(COORD pos, COORD size, int minX, int maxX, bool isLeft)
		: Monster(pos, size, eSpriteType::BOSS_1_IDLE, minX, maxX, 5, isLeft)
		, mCanAttack(false)
		, mDropElapsed(0.f)
		, mIsDrop(false)
		, mArrival(isLeft ? eFlyingOrgePos::LEFT_TOP : eFlyingOrgePos::RIGHT_TOP)
		, mArrivalPos(isLeft ? ORIJIN_LEFT_TOP : ORIJIN_RIGHT_TOP)
	{
	}

	void FlyingOrge::Frame()
	{
		const float DELTA_TIME = TimeManager::GetInstance()->GetDeltaTime();

		mElapsed += DELTA_TIME;
		mDropElapsed += DELTA_TIME;

		handleCollision();

		if (!mIsVaild)
		{
			return;
		}

		handleNextPos();
		handleMove();
		handleAttack();
		handleAnimation();
	}

	void FlyingOrge::handleMove()
	{
		if (mDropElapsed >= ONE_FRAME_TIME * 10)
		{
			mDropElapsed -= ONE_FRAME_TIME;
			mIsDrop = mIsDrop ^ true;
		}

		if (mIsDrop)
		{
			++mPos.Y;
		}
		else
		{
			--mPos.Y;
		}

		if (mElapsed < ONE_FRAME_TIME)
		{
			return;
		}

		mElapsed -= ONE_FRAME_TIME;

		int increaseX = mArrivalPos.X - mPos.X;
		int increaseY = mArrivalPos.Y - mPos.Y;
		int xAmonut = 0;
		int yAmount = 0;

		if (increaseX == 0)
		{
			yAmount = MONSTER_SPEED_VERY_HIGH;
		}
		else if (increaseY == 0)
		{
			xAmonut = MONSTER_SPEED_VERY_HIGH;
		}
		else
		{
			assert(increaseY != 0);

			float slope = increaseY / (float)increaseX;

			if (fabs(slope) < 1.f)
			{
				yAmount = slope * MONSTER_SPEED_VERY_HIGH;
				xAmonut = MONSTER_SPEED_VERY_HIGH;
			}
			else
			{
				yAmount = MONSTER_SPEED_VERY_HIGH;
				xAmonut = MONSTER_SPEED_VERY_HIGH / slope;
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
		mPos.Y = Helper::Clamp(0, 79 - mSize.Y, mPos.Y);
	}

	void FlyingOrge::handleAttack()
	{
		const Object& player = Scene::mScene->GetPlayer();
		COORD playerPos = player.GetPos();

		if (!mCanAttack)
		{
			return;
		}

		mAniElapsed = 0.25f;
		mSpriteType = eSpriteType::BOSS_1_ATTACK;

		EnemyProjectile* proj = new EnemyProjectile(playerPos, mPos, { 4, 4 }, eSpriteType::ENEMY_1_PROJECTILE, mMinX, mMaxX, mIsLeft);
		Helper::Spawn(proj, 4, 4);
		playerPos.Y += 10;
		proj = new EnemyProjectile(playerPos, mPos, { 4, 4 }, eSpriteType::ENEMY_1_PROJECTILE, mMinX, mMaxX, mIsLeft);
		Helper::Spawn(proj, 4, 4);
		playerPos.Y -= 20;
		proj = new EnemyProjectile(playerPos, mPos, { 4, 4 }, eSpriteType::ENEMY_1_PROJECTILE, mMinX, mMaxX, mIsLeft);
		Helper::Spawn(proj, 4, 4);

		mCanAttack = false;
	}

	void FlyingOrge::handleNextPos()
	{
		if (abs(mPos.X - mArrivalPos.X) > 4 || abs(mPos.Y - mArrivalPos.Y) > 4)
		{
			return;
		}

		mCanAttack = true;
		switch (mArrival)
		{
		case eFlyingOrgePos::LEFT_TOP:
			mArrival = eFlyingOrgePos::LEFT_BOTTOM;
			mArrivalPos = ORIJIN_LEFT_BOTTOM;
			mIsLeft = false;
			break;
		case eFlyingOrgePos::RIGHT_TOP:
			mArrival = eFlyingOrgePos::LEFT_TOP;
			mArrivalPos = ORIJIN_LEFT_TOP;
			break;
		case eFlyingOrgePos::LEFT_BOTTOM:
			mArrival = eFlyingOrgePos::RIGHT_BOTTOM;
			mArrivalPos = ORIJIN_RIGHT_BOTTOM;
			break;
		case eFlyingOrgePos::RIGHT_BOTTOM:
			mIsLeft = true;
			mArrival = eFlyingOrgePos::RIGHT_TOP;
			mArrivalPos = ORIJIN_RIGHT_TOP;
			break;
		default:
			assert(false);
			break;
		}
	}

	void FlyingOrge::handleAnimation()
	{
		if (mSpriteType != eSpriteType::BOSS_1_IDLE)
		{
			mAniElapsed -= TimeManager::GetInstance()->GetDeltaTime();
		}

		if (mAniElapsed <= 0.f)
		{
			mAniElapsed = 0.f;
			mSpriteType = eSpriteType::BOSS_1_IDLE;
		}
	}
};
