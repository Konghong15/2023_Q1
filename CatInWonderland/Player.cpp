#include <cassert>
#include <Windows.h>

#include "Player.h"

#include "PlayerIdle.h"
#include "PlayerMove.h"
#include "PlayerAction.h"
#include "PlayerPlummet.h"

#include "InputManager.h"
#include "BoardManager.h"

namespace catInWonderland
{
	Player::Player(const ObjectInfo& objectInfo, size_t boardX, size_t boardY)
		: BoardObject(objectInfo, boardX, boardY)
		, mPlayerState{ nullptr, }
		, mbStageClear(false)
		, mCurrentStateType(ePlayerStateType::Idle)
		, mPreventStateType(ePlayerStateType::Idle)
	{
	}

	Player::Player(hRectangle worldRectangle, hRectangle spriteRectangle, Sprite* sprite, eLayerType layerType, size_t boardX, size_t boardY, bool isLeft)
		: BoardObject(worldRectangle, spriteRectangle, sprite, eObjectType::Player, layerType, boardX, boardY, isLeft)
		, mPlayerState{ nullptr, }
		, mbStageClear(false)
		, mCurrentStateType(ePlayerStateType::Idle)
		, mPreventStateType(ePlayerStateType::Idle)
	{
		mPlayerState[static_cast<unsigned int>(ePlayerStateType::Idle)] = new PlayerIdle();
		mPlayerState[static_cast<unsigned int>(ePlayerStateType::Move)] = new PlayerMove();
		mPlayerState[static_cast<unsigned int>(ePlayerStateType::Action)] = new PlayerAction();
		mPlayerState[static_cast<unsigned int>(ePlayerStateType::Plummet)] = new PlayerPlummet();
	}

	Player::~Player()
	{
		for (int i = 0; i < static_cast<int>(ePlayerStateType::Size); i++)
		{
			delete mPlayerState[i];
			mPlayerState[i] = nullptr;
		}
	}

	void Player::Update()
	{
		PlayerState* currentState = mPlayerState[static_cast<int>(mCurrentStateType)];
		assert(currentState != nullptr);

		currentState->Update(this);
		ePlayerStateType nextStateType = currentState->HandleStateOrNull(this);

		if (mCurrentStateType != nextStateType)
		{
			currentState->Exit(this);
			mPreventStateType = mCurrentStateType;
			mCurrentStateType = nextStateType;
			mPlayerState[static_cast<int>(nextStateType)]->Enter(this);
		}
	}


	void Player::SetIsLeft(bool bLeft)
	{
		mbLeft = bLeft;
		mButterfly->SetIsLeft(bLeft);
	}


	void Player::SetIsRed(bool bRed)
	{
		mButterfly->SetIsRed(bRed);
	}

	bool Player::GetIsRed() const
	{
		return mButterfly->GetIsRed();
	}
}