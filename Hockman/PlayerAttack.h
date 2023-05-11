#pragma once
#pragma once

#include "PlayerState.h"

namespace hockman
{
	class PlayerAttack : public PlayerState
	{
	public:
		PlayerAttack();
		virtual ~PlayerAttack() = default;

		virtual void Enter(Player* player) override;
		virtual PlayerState* HandleInputOrNull(Player* player) override;
		virtual void Update(Player* player) override;

	private:
		float mAttackInterval;
	};
}