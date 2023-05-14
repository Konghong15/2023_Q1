#pragma once

#include <cassert>
#include <map>
#include <vector>

#include "eSprtieType.h"
#include "eAnimationType.h"
#include "hRectangle.h"

namespace catInWonderland
{
	struct Sprite;

	class SpriteManager
	{
	public:
		static SpriteManager* GetInstance();
		static void DeleteInstance();

		inline const Sprite& GetSprite(eSpriteType spriteType);
		inline const hRectangle& GetSpriteRectangle(eAnimationType animationType, bool bLoop, size_t index = 0u);

	private:
		SpriteManager() = default;
		~SpriteManager() = default;

		void init();
		void release();

		void loadSpriteImage(eSpriteType spriteType, const char* fileName);
		void loadAnimationRectangle(eAnimationType animationType, const char* fileName);

	private:
		static SpriteManager* mInstance;

		std::map<eSpriteType, Sprite*> mSpriteMap;
		std::map<eAnimationType, std::vector<hRectangle>> mSpriteRectMap;
	};

	const Sprite& SpriteManager::GetSprite(eSpriteType spriteType)
	{
		auto finded = mSpriteMap.find(spriteType);
		assert(finded != mSpriteMap.end());

		return *(finded->second);
	}

	const hRectangle& SpriteManager::GetSpriteRectangle(eAnimationType animationType, bool bLoop, size_t index)
	{
		auto finded = mSpriteRectMap.find(animationType);
		assert(finded != mSpriteRectMap.end());

		std::vector<hRectangle>& spriteRectangles = (finded->second);
		size_t spriteCount = spriteRectangles.size();
		size_t aniIndex;

		if (bLoop)
		{
			aniIndex = index % spriteCount;
		}
		else
		{
			aniIndex = index < spriteCount ? index : spriteCount - 1;
		}

		assert(index < spriteCount);
		return spriteRectangles.at(aniIndex);
	}
}