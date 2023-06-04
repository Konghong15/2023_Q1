#include "Animator.h"
#include "Object.h"
#include "TimeManager.h"

namespace catInWonderland
{
	Animator::Animator(float interval, const std::vector<hRectangle>& spriteRectangles, bool bLoop)
		: mbLoop(bLoop)
		, mbEnd(false)
		, mInterval(interval)
		, mElapsed(0.f)
		, mIndex(0u)
		, mSpriteRectangles(spriteRectangles)
	{
	}

	void Animator::Update(Object* object)
	{
		if (mbEnd)
		{
			return;
		}

		const float DELTA_TIME = TimeManager::GetInstance()->GetDeltaTime();
		mElapsed += DELTA_TIME;

		if (mInterval < mElapsed)
		{
			mElapsed -= mInterval;

			if (mbLoop)
			{
				mIndex = (mIndex + 1) % mSpriteRectangles.size();
			}
			else
			{
				++mIndex;

				if (mIndex >= mSpriteRectangles.size() - 1)
				{
					mbEnd = true;
				}
			}

			object->SetSpriteRectangle(mSpriteRectangles.at(mIndex));
		}
	}
}