#pragma once

namespace catInWonderland
{
	class SpriteManager;
	class SoundManager;
	class SceneManager;

	class EnumLoader
	{
	public:
		static void LoadSprtie(SpriteManager* const spriteManager);
		static void LoadAnimationRectangle(SpriteManager* const spriteManager);
		static void LoadSound(SoundManager* const soundManager);
		static void LoadScene(SceneManager* const sceneManager);
	};
}