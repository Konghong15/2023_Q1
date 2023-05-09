#pragma once

#include "PlayerState.h"

namespace hockman
{
	class PlayerRun : public PlayerState
	{
	public:
		PlayerRun();
		virtual ~PlayerRun() = default;

		virtual void Enter(Player* player) override;
		virtual PlayerState* HandleInputOrNull(Player* player) override;
		virtual void Update(Player* player) override;

	private:
	};
}