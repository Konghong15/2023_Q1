#pragma once

#include "Object.h"

namespace hockman
{
	class PlayerState;

	class Player final : public Object
	{
	public:
		Player(hRectangle rectangle, eSpriteType spriteType, eObjectType objectType, float moveSpeed);
		~Player() = default;

		virtual void Frame() override;
		virtual void Render() override;

	private:
		float mVX;
		float mVY;
		float mMoveSpeed;

		PlayerState* mPlayerState;
		bool mCanJump;
	};
}