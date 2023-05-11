#pragma once

#include <cassert>
#include <cassert>
#include <vector>
#include "Object.h"

namespace hockman
{
	class PlayerState;

	class Player final : public Object
	{
	public:
		Player(hRectangle worldRectangle, hRectangle uvRectangle, eSpriteType spriteType, eObjectType objectType, float moveSpeed);
		~Player() = default;

		virtual void Frame() override;
		virtual void Render() override;

		// getter
		inline bool IsAniLoop() const;
		inline float GetAniDuration() const;
		inline float GetAniElapsed() const;
		inline const hRectangle& GetUVRectangle()const;
		inline const std::vector<hRectangle>& GetUVRectangles() const;
		inline size_t GetAniIndex() const;
		inline float GetMoveSpeed() const;
		inline float GetVX() const;
		inline float GetVY() const;
		inline float GetGravity() const;

		// setter
		inline void AddAniElapsed(float elapsed);
		inline void AddAniIndex();
		inline void AddVX(float accel);
		inline void AddVY(float accel);

		inline void SetAniIndex(size_t index);
		inline void SetVX(float vx);
		inline void SetVY(float vy);
		inline void SetIsAniLoop(bool isLoop);
		inline void SetAniDuration(float duration);
		inline void SetAniElapsed(float elapsed);
		inline void SetUVRectangle(const hRectangle& rect);
		inline void SetUVRectangles(std::vector<hRectangle>* uvRectangles);
		inline void SetIsRight(bool isRight);

	private:
		enum { MAX_VX = 1000 };
		enum { MAX_VY = 2000 };

		float mVX;
		float mVY;
		float mMoveSpeed;
		float mGravity;
		hRectangle mUVRectangle;

		bool mIsRight;

		bool mIsAniLoop;
		float mAniDuration;
		float mAniElapsed;
		std::vector<hRectangle>* mUVRectangles;
		size_t mAniIndex;

		PlayerState* mPlayerState;
	};

	bool Player::IsAniLoop() const
	{
		return mIsAniLoop;
	}

	void Player::SetIsAniLoop(bool isLoop)
	{
		mIsAniLoop = isLoop;
	}

	float Player::GetAniDuration() const
	{
		return mAniDuration;
	}

	void Player::SetAniDuration(float duration)
	{
		mAniDuration = duration;
	}

	float Player::GetAniElapsed() const
	{
		return mAniElapsed;
	}

	void Player::SetAniElapsed(float elapsed)
	{
		mAniElapsed = elapsed;
	}

	void Player::AddAniElapsed(float elapsed)
	{
		mAniElapsed += elapsed;
	}

	const hRectangle& Player::GetUVRectangle()const
	{
		return mUVRectangle;
	}

	void Player::SetUVRectangle(const hRectangle& rect)
	{
		mUVRectangle = rect;
	}

	const std::vector<hRectangle>& Player::GetUVRectangles() const
	{
		assert(mUVRectangles != nullptr);
		return *mUVRectangles;
	}
	void Player::SetUVRectangles(std::vector<hRectangle>* uvRectangles)
	{
		mUVRectangles = uvRectangles;
	}

	size_t Player::GetAniIndex() const
	{
		return mAniIndex;
	}

	void Player::AddAniIndex()
	{
		++mAniIndex;

		if (mIsAniLoop)
		{
			mAniIndex = mAniIndex < mUVRectangles->size() ? mAniIndex : 0;
		}
		else
		{
			mAniIndex = mAniIndex < mUVRectangles->size() ? mAniIndex : mUVRectangles->size();
			mAniIndex = mAniIndex < mUVRectangles->size() ? mAniIndex : mUVRectangles->size();
		}
	}


	float Player::GetMoveSpeed() const
	{
		return mMoveSpeed;
	}

	void Player::SetIsRight(bool isRight)
	{
		mIsRight = isRight;
	}
	float Player::GetVX() const
	{
		return mVX;
	}
	float Player::GetVY() const
	{
		return mVY;
	}

	float Player::GetGravity() const
	{
		return mGravity;
	}

	void Player::AddVX(float accelX)
	{
		mVX += accelX;

		if (mVX > MAX_VX)
		{
			mVX = MAX_VX;
		}
		else if (mVX < -MAX_VX)
		{
			mVX = -MAX_VX;
		}
	}
	void Player::AddVY(float accelY)
	{
		mVY += accelY;

		if (mVY > MAX_VY)
		{
			mVY = MAX_VY;
		}
		else if (mVY < -MAX_VY)
		{
			mVY = -MAX_VY;
		}
	}

	void Player::SetAniIndex(size_t index)
	{
		mAniIndex = index;
	}

	void Player::SetVX(float vx)
	{
		mVX = vx;

		if (mVX > MAX_VX)
		{
			mVX = MAX_VX;
		}
		else if (mVX < -MAX_VX)
		{
			mVX = -MAX_VX;
		}
	}

	void Player::SetVY(float vy)
	{
		mVY = vy;

		if (mVY > MAX_VY)
		{
			mVY = MAX_VY;
		}
		else if (mVY < -MAX_VY)
		{
			mVY = -MAX_VY;
		}
	}
}