#pragma once

#include "ePlayerState.h"

namespace hockman
{
	class Player;

	class PlayerState
	{
	public:
		PlayerState(ePlayerState playerState)
			: mPlayerState(playerState)
		{
		}
		virtual ~PlayerState() = 0;

		virtual void Enter(Player* player) = 0;
		virtual void HandleInput(Player* player) = 0;
		virtual void Update(Player* player) = 0;

		inline ePlayerState GetPlayerState() const;

	protected:
		ePlayerState mPlayerState;
	};

	ePlayerState PlayerState::GetPlayerState() const
	{
		return mPlayerState;
	}
}