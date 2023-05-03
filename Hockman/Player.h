#pragma once

#include "Object.h"

namespace hockman
{
	class Player final : public Object
	{
	public:
		Player(Vector2 pos, Vector2 size, Vector2 direction, eSpriteType spriteType, eObjectType objectType, float moveSpeed);
		~Player() = default;

		virtual void Frame() override;
		virtual void Render() override;

	private:
		float mMoveSpeed;
	};
}