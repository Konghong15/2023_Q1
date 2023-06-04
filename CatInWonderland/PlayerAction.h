#pragma once

#include "PlayerState.h"

namespace catInWonderland
{
	class Brick;
	class Butterfly;

	class PlayerAction : public PlayerState
	{
	public:
		PlayerAction();
		virtual ~PlayerAction() = default;

		virtual ePlayerStateType HandleStateOrNull(Player* player) override;
		virtual void Enter(Player* player) override;
		virtual void Update(Player* player) override;
		virtual void Exit(Player* player) override;

	private:
		Brick* mBrick;
		float mDistance;
		float mElapsed;
		float mStateEndTime;
	};
}
