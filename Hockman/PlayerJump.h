#pragma once

#include "PlayerState.h"

namespace hockman
{
	class PlayerJump : public PlayerState
	{
	public:
		PlayerJump();
		virtual ~PlayerJump() = default;

		virtual void Enter(Player* player) override;
		virtual PlayerState* HandleInputOrNull(Player* player) override;
		virtual void Update(Player* player) override;

	private:
		bool mIsDown;
		bool mIsEnd;
	};
}