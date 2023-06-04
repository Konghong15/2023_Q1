#include "Button.h"
#include "InputManager.h"

namespace catInWonderland
{
	Button::Button(const ObjectInfo& objectInfo)
		: Object(objectInfo)
		, mButtonState(eButtonState::None)
	{
	}

	Button::Button(hRectangle worldRectangle, hRectangle spriteRectangle, Sprite* sprite, eLayerType layerType, bool bLeft)
		: Object(worldRectangle, spriteRectangle, sprite, eObjectType::None, layerType, bLeft)
		, mButtonState(eButtonState::None)
	{
	}

	void Button::Update()
	{
		const POINT& mousePos = InputManager::GetInstance()->GetMousePos();
		
		// (°æ°í) float -> const long
		if (hRectangle::IsContainVertex(mWorldRectangle, static_cast<float>(mousePos.x), static_cast<float>(mousePos.y)))
		{
			if (InputManager::GetInstance()->GetKeyState(VK_LBUTTON) == eKeyState::PUSH)
			{
				mButtonState = eButtonState::Click;
			}
			else
			{
				mButtonState = eButtonState::Hover;
			}
		}
		else
		{
			mButtonState = eButtonState::None;
		}
	}
}
