#pragma once

#include "Object.h"

namespace hockman
{
	class Enemy final : public Object
	{
	public:
		Enemy(hRectangle rectangle, eSpriteType spriteType, float moveSpeed);
		~Enemy() = default;

		virtual void Frame() override;
		virtual void Render() override;

	private:
		float mMoveSpeed;
	};
}