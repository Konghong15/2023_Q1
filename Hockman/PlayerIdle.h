#pragma once

#include "PlayerState.h"

namespace hockman
{
	class PlayerIdle : public PlayerState
	{
	public:
		PlayerIdle();
		virtual ~PlayerIdle() = default;

		virtual void Enter(Player* player) override;
		virtual PlayerState* HandleInputOrNull(Player* player) override;
		virtual void Update(Player* player) override;

	private:
	};
}