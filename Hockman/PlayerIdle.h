#pragma once

#include "PlayerState.h"

namespace hockman
{
	class PlayerIdle : public PlayerState
	{
		PlayerIdle() = default;
		virtual ~PlayerIdle() = default;

		virtual void Enter(Player* player) override;
		virtual void HandleInput(Player* player) override;
		virtual void Update(Player* player) override;

	private:
	};
}