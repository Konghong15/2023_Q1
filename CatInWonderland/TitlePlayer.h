#pragma once

#include "Object.h"
#include "Animator.h"

namespace catInWonderland
{
	class TitlePlayer : public Object
	{
	public:
		TitlePlayer(hRectangle worldRectangle, eLayerType layerType);
		virtual ~TitlePlayer() = default;

		virtual void Update(float deltaTime) override;

		inline void Excute();
		inline void SetAnimator(const Animator& animator);

	private:
		Animator mAnimator;
		bool mbExcute;
	};

	void TitlePlayer::Excute()
	{
		mbExcute = true;
	}

	void TitlePlayer::SetAnimator(const Animator& animator)
	{
		mAnimator = animator;
	}
}