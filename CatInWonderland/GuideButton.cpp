#include "GuideButton.h"
#include "TimeManager.h"

namespace catInWonderland
{
	GuideButton::GuideButton(hRectangle worldRectangle, hRectangle spriteRectangle, Sprite* sprite, eLayerType layerType, float duration)
		: Object(worldRectangle, spriteRectangle, sprite, eObjectType::None, layerType)
		, mDuration(duration)
		, mElapesed(0.f)
		, mbExcute(false)
	{
	}

	void GuideButton::Update()
	{
		if (!mbExcute)
		{
			return;
		}

		const float DELTA_TIME = TimeManager::GetInstance()->GetDeltaTime();

		mElapesed += DELTA_TIME;

		if (mDuration < mElapesed)
		{
			mbExcute = false;
			mElapesed = 0.f;
		}
	}

	void GuideButton::Render()
	{
		if (mbExcute)
		{
			Object::Render();
		}
	}
}