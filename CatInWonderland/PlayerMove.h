#pragma once

#include "PlayerState.h"
#include "Object.h"

namespace catInWonderland
{
	class Butterfly;

	class PlayerMove : public PlayerState
	{
	public:
		PlayerMove();
		virtual ~PlayerMove() = default;

		virtual ePlayerStateType HandleStateOrNull(Player* player);
		virtual void Enter(Player* player) override;
		virtual void Update(Player* player);
		virtual void Exit(Player* player);

		inline const hRectangle& GetWorldRectangle() const;

	private:
		const float mStateEndTime;
		hRectangle mWorldRectangle;
		int mMoveX;
		float mDistance;
		float mElapsed;
		float mMaxOffset;
	};

	const hRectangle& PlayerMove::GetWorldRectangle() const
	{
		return mWorldRectangle;
	}
}