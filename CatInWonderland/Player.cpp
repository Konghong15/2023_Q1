#include "Player.h"
#include "InputManager.h"
#include "BoardManager.h"
#include "TimeManager.h"
#include "RenderManager.h"

namespace catInWonderland
{
	Player::Player(hRectangle rectangle, size_t indexX, size_t indexY)
		: Object(rectangle, indexX, indexY)
		, mbRight(true)
	{
	}

	void Player::Frame()
	{
		const size_t BOARD_SIZE = BoardManager::GetInstance()->GetBoardSize();

		if (InputManager::GetInstance()->GetKeyState('A') == eKeyState::PUSH)
		{
			mIndexX = mIndexX != 0 ? mIndexX - 1 : mIndexX;
			mRectangle = BoardManager::GetInstance()->GetWorldRect(mIndexX, mIndexY);
		}
		else if (InputManager::GetInstance()->GetKeyState('D') == eKeyState::PUSH)
		{
			mIndexX = mIndexX < BOARD_SIZE - 1 ? mIndexX + 1 : mIndexX;
			mRectangle = BoardManager::GetInstance()->GetWorldRect(mIndexX, mIndexY);
		}
	}

	void Player::Render()
	{
		RenderManager::GetInstance()->Draw(mRectangle, eSpriteType::Player, eAnimationType::None, 0);
	}
}