#include "PlummetObject.h"
#include "TimeManager.h"

namespace catInWonderland
{
	PlummetObject::PlummetObject(hRectangle worldRectangle, hRectangle spriteRectangle, Sprite* sprite, eLayerType layerType, float duration, float plummetDistance)
		: Object(worldRectangle, spriteRectangle, sprite, eObjectType::None, layerType)
		, mDuration(duration)
		, mPlummetDistance(plummetDistance)
		, mbIsErase(false)
		, mEraseTime(0.f)
		, mbExcute(false)
		, mElapesed(0.f)
	{
	}

	void PlummetObject::Update()
	{
		if (!mbExcute)
		{
			return;
		}

		const float DELTA_TIME = TimeManager::GetInstance()->GetDeltaTime();

		if (mDuration > mElapesed)
		{
			MoveInWorld(0, mPlummetDistance * DELTA_TIME / mDuration);
			mElapesed += DELTA_TIME;
		}

		if (mbIsErase)
		{
			mEraseTime -= DELTA_TIME;

			if (mEraseTime < 0.f)
			{
				mbExcute = false;
			}
		}
	}

	void PlummetObject::Render()
	{
		if (mbExcute)
		{
			Object::Render();
		}
	}
}