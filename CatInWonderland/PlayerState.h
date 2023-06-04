#pragma once

#include <vector>

#include "ePlayerStateType.h"
#include "hRectangle.h"
#include "Animator.h"

namespace catInWonderland
{
	class Player;

	class PlayerState
	{
	public:
		PlayerState(ePlayerStateType playerState, const Animator& animator);
		virtual	~PlayerState() = default;

		virtual ePlayerStateType HandleStateOrNull(Player* player) = 0;
		virtual void Enter(Player* player);
		virtual void Update(Player* player);
		virtual void Exit(Player* player);

		inline ePlayerStateType GetPlayerState() const;

	protected:
		void HandlePortal(Player* player);
		void HandleColorChange(Player* player);

	protected:
		ePlayerStateType mPlayerState;
		Animator mAnimator;
	};

	ePlayerStateType PlayerState::GetPlayerState() const
	{
		return mPlayerState;
	}
}