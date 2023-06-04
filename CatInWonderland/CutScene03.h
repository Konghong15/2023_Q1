#pragma once

#include "CutScene.h"

namespace catInWonderland
{
	struct Sprite;

	class CutScene03 : public CutScene
	{
	public:
		CutScene03();
		virtual ~CutScene03() = default;

		virtual eSceneType HandleScene() override;
		virtual void Enter() override;
		virtual void Update() override;
		virtual void Exit() override;

	private:
		enum { SPRITE_SIZE = 5 };

		Sprite* mMapSprites[SPRITE_SIZE];
		float mElapsed;
		bool mbEnd;
		unsigned int mSpriteIndex;
	};
}
