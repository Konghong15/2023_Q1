#pragma once

#include "Object.h"

namespace hongpireSurvivors
{
	enum class eButtonState
	{
		NONE,
		HOVER,
		CLICK
	};

	class Button : public Object
	{
		friend class Scene;

	public:
		Button(COORD pos, COORD size, eSpriteType spriteType, eObjectType objectType, bool isLeft = true);
		virtual ~Button() = default;

		virtual void Frame() override;

		inline bool GetIsClick() const;

	private:
		eButtonState mButtonState;
		bool mIsClicked;
	};

	bool Button::GetIsClick() const
	{
		return mIsClicked;
	}
}