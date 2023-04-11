#pragma once

#include "Monster.h"

namespace hongpireSurvivors
{
	enum class eFlyingOrgePos
	{
		LEFT_TOP,
		RIGHT_TOP,
		LEFT_BOTTOM,
		RIGHT_BOTTOM
	};

	class FlyingOrge : public Monster
	{
	public:
		FlyingOrge(COORD pos, COORD size, int minX, int maxX, bool isLeft = true);
		virtual ~FlyingOrge() = default;

		virtual void Frame() override;

	private:
		virtual void handleMove() override;
		void handleAttack();
		void handleNextPos();
		void handleAnimation();

	private:
		static CONST COORD ORIJIN_LEFT_TOP;
		static CONST COORD ORIJIN_RIGHT_TOP;
		static CONST COORD ORIJIN_LEFT_BOTTOM;
		static CONST COORD ORIJIN_RIGHT_BOTTOM;

		bool mCanAttack;
		float mDropElapsed;
		float mAniElapsed;
		bool mIsDrop;
		eFlyingOrgePos mArrival;
		COORD mArrivalPos;
	};
}