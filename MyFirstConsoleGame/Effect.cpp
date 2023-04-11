#include "Effect.h"
#include "TimeManager.h"
#include "RenderManager.h"
#include "Scene.h"

namespace hongpireSurvivors
{
	Effect::Effect(COORD pos, COORD size, eSpriteType* spriteTypes, size_t spriteLength, float spriteDuration, WORD color, bool isLeft)
		: Object(pos, size, spriteTypes[0], eObjectType::EFFECT, isLeft)
		, mIndex(0u)
		, mSpriteLength(spriteLength)
		, mSpriteDuration(spriteDuration)
		, mColor(color)
		, mElapsed(0.f)
	{
		mSptieTypes = new eSpriteType[mSpriteLength + 1];
		for (int i = 0; i < spriteLength; ++i)
		{
			mSptieTypes[i] = spriteTypes[i];
		}
	}

	Effect::~Effect()
	{
		delete[] mSptieTypes;
		mSptieTypes = nullptr;
	}

	void Effect::Frame()
	{
		const float DELTA_TIME = TimeManager::GetInstance()->GetDeltaTime();

		mElapsed += DELTA_TIME;

		if (mElapsed >= mSpriteDuration)
		{
			mElapsed -= mSpriteDuration;
			++mIndex;
		}

		if (mIndex >= mSpriteLength)
		{
			mIsVaild = false;
			mIndex = mSpriteLength - 1;
		}
	}

	void Effect::Render()
	{
		int x = mPos.X - Scene::mScene->GetCamara().X;

		if (x >= 0 && x + mSize.X < 400)
		{
			RenderManager::GetInstance()->Draw(x, mPos.Y, mSptieTypes[mIndex], mColor, mIsLeft);
		}
	}
}