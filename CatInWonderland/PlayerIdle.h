#pragma once

#include <vector>

#include "PlayerState.h"
#include "hRectangle.h"
#include "Butterfly.h"

namespace catInWonderland
{
	class Player;

	class PlayerIdle : public PlayerState
	{
	public:
		PlayerIdle();
		~PlayerIdle() = default;

		virtual ePlayerStateType HandleStateOrNull(Player* player);
		virtual void Enter(Player* player);
	};
}
