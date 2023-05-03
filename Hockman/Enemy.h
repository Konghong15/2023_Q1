#pragma once

#include "Object.h"

namespace hockman
{
	class Enemy final : public Object
	{
	public:
		Enemy(Vector2 pos, Vector2 size, Vector2 direction, eSpriteType spriteType, float moveSpeed);
		~Enemy() = default;

		virtual void Frame() override;
		virtual void Render() override;

	private:
		float mMoveSpeed;
	};
}