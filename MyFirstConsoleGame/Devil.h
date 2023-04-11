#pragma once

#include "Monster.h"

namespace hongpireSurvivors
{
	enum class eDevilState
	{
		MOVE,
		LONG_LRANGE_ATTACK,
		CLOSE_RANGE_ATTACK
	};

	class Devil : public Monster
	{
	public:
		Devil(COORD pos, COORD size, int minX, int maxX, bool isLeft = true);
		virtual ~Devil() = default;

		virtual void Frame() override;

	protected:
		virtual void handleMove() override;
		void handleAttack();
		void handleState();

	private:
		COORD mArrivalPos;
		COORD mStartPos;

		eDevilState mDevildState;
		bool mCanAttack;
		float mMaxElapsed;
		float mAttackElapsed;
		unsigned int mMoveCount;
	};
}