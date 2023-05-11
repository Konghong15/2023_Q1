#pragma once

#include "PlayerState.h"

namespace hockman
{
	class PlayerNonAttack : public PlayerState
	{
	public:
		PlayerNonAttack();
		virtual ~PlayerNonAttack() = default;

		virtual void Enter(Player* player) override;
		virtual PlayerState* HandleInputOrNull(Player* player) override;
		virtual void Update(Player* player) override;
	
	private:
		float mKeyElapsedTime;
	};
}