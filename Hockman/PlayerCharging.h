#pragma once

#include "PlayerState.h"

namespace hockman
{
	class PlayerCharging : public PlayerState
	{
	public:
		PlayerCharging();
		virtual ~PlayerCharging() = default;

		virtual void Enter(Player* player) override;
		virtual PlayerState* HandleInputOrNull(Player* player) override;
		virtual void Update(Player* player) override;

	private:
		float mKeyElapsedTime;
		float mAniElpased;
	};
}