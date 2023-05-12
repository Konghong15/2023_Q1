#include "PlayerState.h"

namespace hockman
{
	std::vector<hRectangle> PlayerState::mIdleUVRects;
	std::vector<hRectangle> PlayerState::mRunUVRects;
	std::vector<hRectangle> PlayerState::mJumpUVRects;

	void PlayerState::Init()
	{
		mIdleUVRects.reserve(2);
		mIdleUVRects.emplace_back(32, 33, 64, 64);
		mIdleUVRects.emplace_back(64, 33, 96, 64);
		mIdleUVRects.emplace_back(96, 33, 128, 64);

		mRunUVRects.reserve(4);
		mRunUVRects.emplace_back(128, 33, 160, 64);
		mRunUVRects.emplace_back(160, 33, 192, 64);
		mRunUVRects.emplace_back(192, 33, 224, 64);

		mJumpUVRects.reserve(2);
		mJumpUVRects.emplace_back(224, 33, 256, 64);
		mJumpUVRects.emplace_back(256, 33, 288, 64);
	}

	void PlayerState::Release()
	{
		mIdleUVRects.clear();
		mRunUVRects.clear();
		mJumpUVRects.clear();
	}

	PlayerState::PlayerState(ePlayerState playerState)
		: mPlayerState(playerState)
	{
	}
}