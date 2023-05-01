#include "Projectile.h"
#include "RenderManager.h"
#include "TimeManager.h"
#include "ColliderManager.h"
#include "ObjectManager.h"
#include "Effect.h"
#include "SceneManager.h"
#include "Scene.h"

namespace hongpireSurvivors
{
	Projectile::Projectile(COORD pos, COORD size, eSpriteType spriteType, bool isLeft)
		: Object(pos, size, spriteType, eObjectType::PROJECTILE, isLeft)
		, START_POS(pos)
		, mElapsed(0.f)
	{
	}

	void Projectile::Frame()
	{
		const float DELTA_TIME = TimeManager::GetInstance()->GetDeltaTime();
		mElapsed += DELTA_TIME;

		handleCollision();

		if (!mIsVaild)
		{
			return;
		}

		handleMove();
	}

	void Projectile::handleMove()
	{
		if (mElapsed < ONE_FRAME_TIME)
		{
			return;
		}

		mElapsed -= ONE_FRAME_TIME;

		if (mIsLeft)
		{
			mPos.X -= PROJECTILE_SPEED_MIDDLE;
		}
		else
		{
			mPos.X += PROJECTILE_SPEED_MIDDLE;
		}
	}

	void Projectile::handleCollision()
	{
		int flag = mCollider->GetEnterBitFlag();
		int mask = static_cast<int>(eObjectType::ENEMY);

		if ((flag & mask) != 0 || abs(START_POS.X - mPos.X) > 200)
		{
			eSpriteType spriteTypes[1] = { eSpriteType::PROJECTIE_EFFECT };
			Effect* effect = new Effect({ (SHORT)(mPos.X), (SHORT)(mPos.Y) }, { (SHORT)10, (SHORT)10 }, spriteTypes, 1, 0.25f, RenderManager::GetInstance()->GetColor(eConsoleColor::BLACK, eConsoleColor::WHITE), mIsLeft);
			ObjectManager::GetInstance()->OnSpawn(effect);

			mIsVaild = false;
			return;
		}
	}

	void Projectile::Render()
	{
		int x = mPos.X - SceneManager::GetInstance()->GetCurScene()->GetCamaraPos().X;

		if (x >= 0 && x + mSize.X < 400)
		{
			RenderManager::GetInstance()->Draw(x, mPos.Y, mSpriteType, RenderManager::GetInstance()->GetColor(eConsoleColor::BLACK, eConsoleColor::DEEP_WHITE), mIsLeft);
		}
	}
}