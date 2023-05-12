#pragma once

#include <vector>

#include "ePlayerState.h"
#include "hRectangle.h"

namespace hockman
{
	class Player;

	class PlayerState
	{
	public:
		PlayerState(ePlayerState playerState);
		virtual ~PlayerState() = default; // ¿Ö why~

		virtual void Enter(Player* player) = 0;
		virtual PlayerState* HandleInputOrNull(Player* player) = 0;
		virtual void Update(Player* player) = 0;

		inline ePlayerState GetPlayerState() const;

		static void Init();
		static void Release();

	protected:
		static std::vector<hRectangle> mIdleUVRects;
		static std::vector<hRectangle> mRunUVRects;
		static std::vector<hRectangle> mJumpUVRects;

		ePlayerState mPlayerState;
	};

	ePlayerState PlayerState::GetPlayerState() const
	{
		return mPlayerState;
	}
}