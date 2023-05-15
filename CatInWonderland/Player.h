#pragma once

#include "Object.h"

namespace catInWonderland
{
	class Player final : public Object
	{
	public:
		Player(hRectangle rectangle, size_t indexX, size_t indexY);
		~Player() = default;

		virtual void Frame() override;
		virtual void Render() override;

	private:
		bool mbRight;
	};
}