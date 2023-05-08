#include "Monster.h"

namespace hongpireSurvivors
{
	class Orge : public Monster
	{
	public:


		Orge(COORD pos, COORD size, int minX, int maxX, bool isLeft = true);
		virtual ~Orge() = default;

		virtual void Frame() override;

	protected:
		virtual void handleMove() override;
		void handleJump();
		void handleAttack();

	private:
		SHORT mArrival;
		bool mCanAttack;
		float mAttackElapsed;
		float mDropElapsed;
		float mJumpForce;
		bool mIsJump;
	};
}