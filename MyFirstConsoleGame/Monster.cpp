#include "Monster.h"
#include "RenderManager.h"
#include "TimeManager.h"
#include "ColliderManager.h"
#include "Scene.h"
#include "SoundManager.h"

namespace hongpireSurvivors
{
	Monster::Monster(COORD pos, COORD size, eSpriteType spriteType, int minX, int maxX, int hp, bool isLeft)
		: Object(pos, size, spriteType, eObjectType::ENEMY, isLeft)
		, mElapsed(0.f)
		, START_POS(pos)
		, mHp(hp)
		, mMinX(minX)
		, mMaxX(maxX)
	{
	}

	void Monster::Frame()
	{
		const float DELTA_TIME = TimeManager::GetInstance()->GetDeltaTime();
		mElapsed += DELTA_TIME;

		handleCollision();

		if (!mIsVaild)
		{
			return;
		}

		handleMove();
		handleDirection();
	}

	void Monster::handleCollision()
	{
		int flag = mCollider->GetEnterBitFlag();
		int mask = static_cast<int>(eObjectType::PROJECTILE);

		if ((flag & mask) != 0)
		{
			--mHp;

			if (mHp <= 0)
			{
				SoundManager::GetInstance()->Play(eSound::MONSTER_DEATH);
				mIsVaild = false;
			}
			else
			{
				SoundManager::GetInstance()->Play(eSound::MONSTER_HIT);
			}
		}

	}

	void Monster::handleDirection()
	{
		if (mPos.X <= mMinX)
		{
			mIsLeft = false;
			mPos.X = mMinX;
		}
		else if (mPos.X >= mMaxX - mSize.X - 1)
		{
			mIsLeft = true;
			mPos.X = mMaxX - mSize.X - 1;
		}
	}

	void Monster::Render()
	{
		int x = mPos.X - Scene::mScene->GetCamara().X;

		if (x >= 0 && x + mSize.X < 400)
		{
			RenderManager::GetInstance()->Draw(x, mPos.Y, mSpriteType, RenderManager::GetInstance()->GetColor(eConsoleColor::BLACK, eConsoleColor::RED), mIsLeft);
		}
	}
}