#pragma once

#include "Object.h"
#include "Animator.h"
#include "Player.h"
#include "BoardObject.h"

namespace catInWonderland
{
	class Butterfly : public Object
	{
	public:
		Butterfly(const ObjectInfo& objectInfo, Object* interactionObjectOrNull, float maxOffset, bool bRed, const Animator& animator);
		Butterfly(hRectangle worldRectangle, hRectangle spriteRectangle, eSpriteType spriteType, eObjectType objectType, Object* interactionObjectOrNull, eLayerType layerType, float maxOffset, bool bRed, bool bLeft, const Animator& animator);
		virtual ~Butterfly() = default;

		virtual void Update(float deltaTime) override;

		void InvertColor();
		void SetIsRed(bool bRed);
		inline void SetInteractionObject(Object* interactionObject);
		inline void SetMaxOffset(float maxOffSet);

		inline bool GetIsRed() const;

	private:
		// 클래스 내부에서만 접근할 수 있어?
		// 클래스 내부에서만 쓸려고, 클래스 내부만 쓰는 함수는 중복 로직 제거를 위해서

	private:
		Object* mInteractionObjectOrNull;
		Animator mAnimator;
		float mMaxOffset;
		bool mbRed;
	};

	void Butterfly::SetInteractionObject(Object* interactionObject)
	{
		mInteractionObjectOrNull = interactionObject;
	}

	void Butterfly::SetMaxOffset(float maxOffSet)
	{
		mMaxOffset = maxOffSet;
	}

	bool Butterfly::GetIsRed() const
	{
		return mbRed;
	}


}