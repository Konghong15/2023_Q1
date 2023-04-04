#pragma once

#include <cassert>
#include <Windows.h>
#include <map>

#include "eSpriteType.h"
#include "Sprite.h"

namespace hongpireSurvivors
{
	class SpriteManager
	{
	public:
		static SpriteManager* GetInstance();
		static void DeleteInstance();

		inline const Sprite& GetSprite(eSpriteType spriteType);

	private:
		SpriteManager();
		~SpriteManager() = default;

		void load(eSpriteType spriteType, const char* fileName);

	private:
		static SpriteManager* mInstance;

		std::map<eSpriteType, Sprite*> mSpriteMap;
	};

	const Sprite& SpriteManager::GetSprite(eSpriteType spriteType)
	{
		auto finded = mSpriteMap.find(spriteType);
		assert(finded != mSpriteMap.end());

		return *(finded->second);
	}
}