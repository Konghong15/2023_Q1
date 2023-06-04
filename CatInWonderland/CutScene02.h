#pragma once

#include "CutScene.h"

namespace catInWonderland
{
	struct Sprite;

	class CutScene02 : public CutScene
	{
	public:
		CutScene02();
		virtual ~CutScene02() = default;

		virtual eSceneType HandleScene() override;
		virtual void Enter() override;
		virtual void Update() override;
		virtual void Exit() override;

	private:
		enum { SPRITE_SIZE = 4 };

		Sprite* mMapSprites[SPRITE_SIZE];
		float mElapsed;
		bool mbEnd;
		unsigned int mSpriteIndex;
	};
}
