#pragma once

#include "PlayerState.h"

namespace hockman
{
	class PlayerJump : public PlayerState
	{
		PlayerJump();
		virtual ~PlayerJump() = default;

		virtual void Enter(Player* player) override;
		virtual void HandleInput(Player* player) override;
		virtual void Update(Player* player) override;

	private:
	};
}