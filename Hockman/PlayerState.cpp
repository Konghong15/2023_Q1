#include "PlayerState.h"

namespace hockman
{
	std::vector<hRectangle> PlayerState::mIdleUVRects;
	std::vector<hRectangle> PlayerState::mRunUVRects;
	std::vector<hRectangle> PlayerState::mJumpUVRects;

	void PlayerState::Init()
	{
		mIdleUVRects.reserve(2);
		mIdleUVRects.emplace_back(32, 33, 32, 32);
		mIdleUVRects.emplace_back(64, 33, 32, 32);
		mIdleUVRects.emplace_back(96, 33, 32, 32);

		mRunUVRects.reserve(4);
		mRunUVRects.emplace_back(128, 33, 32, 32);
		mRunUVRects.emplace_back(160, 33, 32, 32);
		mRunUVRects.emplace_back(192, 33, 32, 32);

		mJumpUVRects.reserve(2);
		mJumpUVRects.emplace_back(224, 33, 32, 32);
		mJumpUVRects.emplace_back(256, 33, 32, 32);
	}

	PlayerState::PlayerState(ePlayerState playerState)
		: mPlayerState(playerState)
	{
	}
}