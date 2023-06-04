#pragma once

#include "Object.h"
#include "eLayerType.h"

namespace catInWonderland
{
	class PlummetObject : public Object
	{
	public:
		PlummetObject(hRectangle worldRectangle, hRectangle spriteRectangle, eSpriteType spriteType, eLayerType layerType, float duration, float plummetDistance);
		virtual ~PlummetObject() = default;

		virtual void Update(float deltaTime) override;

		inline void Excute();
		inline void SetEraseTime(float eraseTime);

		inline bool GetExcute() const;

	private:
		bool mbExcute;
		float mDuration;
		float mElapesed;
		float mPlummetDistance;

		bool mbIsErase;
		float mEraseTime;
	};

	void PlummetObject::Excute()
	{
		mbExcute = true;
	}

	void PlummetObject::SetEraseTime(float eraseTime)
	{
		if (!mbIsErase)
		{
			mbIsErase = true;
			mEraseTime = eraseTime;
		}
	}

	bool PlummetObject::GetExcute() const
	{
		return mbExcute;
	}
}