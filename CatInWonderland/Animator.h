#pragma once

#include <cassert>
#include <vector>

#include "hRectangle.h"

namespace catInWonderland
{
	class Object;

	class Animator
	{
	public:
		Animator(float interval, const std::vector<hRectangle>& spriteRectangles, bool bLoop);
		virtual ~Animator() = default;

		void Update(Object* object);

		inline bool GetIsEnd() const;
		inline const hRectangle& GetSpriteRectangle(unsigned int index) const;

	private:
		bool mbLoop;
		bool mbEnd;
		float mInterval;
		float mElapsed;
		unsigned int mIndex;
		std::vector<hRectangle> mSpriteRectangles;
	};

	bool Animator::GetIsEnd() const
	{
		return mbEnd;
	}

	inline const hRectangle& Animator::GetSpriteRectangle(unsigned int index) const
	{
		assert(index < mSpriteRectangles.size());

		return mSpriteRectangles.at(index);
	}
}