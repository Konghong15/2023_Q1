#include <cassert>

#include "Button.h"
#include "InputManager.h"
#include "Helper.h"

namespace hongpireSurvivors
{
	Button::Button(COORD pos, COORD size, eSpriteType spriteType, eObjectType objectType, bool isLeft)
		: Object(pos, size, spriteType, objectType, isLeft)
		, mButtonState(eButtonState::NONE)
		, mIsClicked(false)
	{
	}

	void Button::Frame()
	{
		const POINT& mousePos = InputManager::GetInstance()->GetMousePos();
		if (!Helper::IsContain(mPos, mSize, mousePos))
		{
			mButtonState = eButtonState::NONE;
			return;
		}

		switch (mButtonState)
		{
		case eButtonState::NONE:
			eButtonState::HOVER;
			break;
		case eButtonState::HOVER:
			if (InputManager::GetInstance()->GetKeyState(VK_LBUTTON) == eKeyState::POP)
			{
				mButtonState = eButtonState::CLICK;
			}
			break;
		case eButtonState::CLICK:
			eButtonState::NONE;
			mIsClicked = true;
			break;
		default:
			assert(false);
			break;
		}
	}
}