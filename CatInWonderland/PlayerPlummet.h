#pragma once

#include "PlayerState.h"

namespace catInWonderland
{
	class Butterfly;

	class PlayerPlummet : public PlayerState
	{
	public:
		PlayerPlummet();
		virtual ~PlayerPlummet() = default;

		virtual ePlayerStateType HandleStateOrNull(Player* player);
		virtual void Enter(Player* player);
		virtual void Update(Player* player);
		virtual void Exit(Player* player);

	private:
		const float mStateEndTime;
		float mDistance;
		float mElapsed;

		size_t mMovedBoardY;
	};
}