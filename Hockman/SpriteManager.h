#pragma once

#include <cassert>
#include <map>

#include "eSpriteType.h"

namespace hockman
{
	class Sprite;

	class SpriteManager
	{
	public:
		static SpriteManager* GetInstance();
		static void DeleteInstance();

		void Init();
		void Release();

		inline const Sprite& GetSprite(eSpriteType spriteType);

	private:
		SpriteManager() = default;
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