#pragma once

#include "PlayerState.h"

namespace hockman
{
	class PlayerRun : public PlayerState
	{
		PlayerRun();
		virtual ~PlayerRun() = default;

		virtual void Enter(Player* player) override;
		virtual void HandleInput(Player* player) override;
		virtual void Update(Player* player) override;

	private:
	};
}