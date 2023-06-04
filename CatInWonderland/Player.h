#pragma once

#include "BoardObject.h"
#include "ePlayerStateType.h"
#include "PlayerState.h"

namespace catInWonderland
{
	class Butterfly;

	class Player final : public BoardObject
	{
		friend class PlayerAction;
		friend class PlayerState;

	public:
		Player(const ObjectInfo& objectInfo, size_t boardX, size_t boardY);
		Player(hRectangle worldRectangle, hRectangle spriteRectangle, eSpriteType spriteType, eLayerType layerType, size_t boardX, size_t boardY, bool bLeft = true);
		~Player() override;

		void Update(float deltaTime) override;

		virtual void SetIsLeft(bool bLeft);
		void SetIsRed(bool bRed);
		inline void SetButterfly(Butterfly* butterfly);

		bool GetIsRed() const;
		inline ePlayerStateType GetPlayerState() const;
		inline ePlayerStateType GetPreventPlayerState() const;
		inline bool GetStageClear() const;

	private:
		inline void SetStageClear(bool bStageClear);
		inline Butterfly* GetButterfly();

	private:
		ePlayerStateType mCurrentStateType;
		ePlayerStateType mPreventStateType;
		PlayerState* mPlayerState[static_cast<unsigned int>(ePlayerStateType::Size)];
		Butterfly* mButterfly;
		bool mbStageClear;
	};

	ePlayerStateType Player::GetPlayerState() const
	{
		return mCurrentStateType;
	}

	ePlayerStateType Player::GetPreventPlayerState() const
	{
		return mPreventStateType;
	}

	bool Player::GetStageClear() const
	{
		return mbStageClear;
	}

	void Player::SetStageClear(bool bStageClear)
	{
		mbStageClear = bStageClear;
	}


	void Player::SetButterfly(Butterfly* butterfly)
	{
		mButterfly = butterfly;
	}

	Butterfly* Player::GetButterfly()
	{
		return mButterfly;
	}
}