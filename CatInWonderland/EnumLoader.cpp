#include "EnumLoader.h"
#include "SpriteManager.h"
#include "eSpriteType.h"
#include "SceneLoader.h"
#include "SoundManager.h"
#include "ConstantTable.h"

namespace catInWonderland
{
	void EnumLoader::LoadSprtie(SpriteManager* const spriteManager)
	{
		assert(spriteManager != nullptr);

		spriteManager->LoadSpriteImage(eSpriteType::Player, L".\\resources\\image\\player.bmp");
		spriteManager->LoadSpriteImage(eSpriteType::YellowTile, L".\\resources\\image\\1-2.nonblendblock.bmp");
		spriteManager->LoadSpriteImage(eSpriteType::NonBlendYellowTile, L".\\resources\\image\\1-2.block.bmp");
		spriteManager->LoadSpriteImage(eSpriteType::NonBlendPurpleTile, L".\\resources\\image\\3-5.block.bmp");
		spriteManager->LoadSpriteImage(eSpriteType::PurpleTile, L".\\resources\\image\\3-5.nonblendblock.bmp");
		spriteManager->LoadSpriteImage(eSpriteType::RedBrick, L".\\resources\\image\\red_brick.bmp");
		spriteManager->LoadSpriteImage(eSpriteType::BlueBrick, L".\\resources\\image\\blue_brick.bmp");
		spriteManager->LoadSpriteImage(eSpriteType::Butterfly, L".\\resources\\image\\burterfly_sprite.bmp");
		spriteManager->LoadSpriteImage(eSpriteType::Obstacle, L".\\resources\\image\\block_object.bmp");
		spriteManager->LoadSpriteImage(eSpriteType::BlueChangeColorTile, L".\\resources\\image\\blue_cube.bmp");
		spriteManager->LoadSpriteImage(eSpriteType::RedChangeColorTile, L".\\resources\\image\\red_cube.bmp");
		spriteManager->LoadSpriteImage(eSpriteType::YellowPortal, L".\\resources\\image\\yellow_portal.bmp");
		spriteManager->LoadSpriteImage(eSpriteType::PurplePortal, L".\\resources\\image\\purple_portal.bmp");
		spriteManager->LoadSpriteImage(eSpriteType::Challange, L".\\resources\\image\\challange1.bmp");
		spriteManager->LoadSpriteImage(eSpriteType::TitleText, L".\\resources\\image\\title_text.bmp");
		spriteManager->LoadSpriteImage(eSpriteType::MainTitle, L".\\resources\\image\\main_title.bmp");
		spriteManager->LoadSpriteImage(eSpriteType::Stage01, L".\\resources\\image\\stage01_map.bmp");
		spriteManager->LoadSpriteImage(eSpriteType::Stage02, L".\\resources\\image\\stage02_map.bmp");
		spriteManager->LoadSpriteImage(eSpriteType::Stage03, L".\\resources\\image\\stage03_map.bmp");
		spriteManager->LoadSpriteImage(eSpriteType::Stage04, L".\\resources\\image\\stage04_map.bmp");
		spriteManager->LoadSpriteImage(eSpriteType::Stage05, L".\\resources\\image\\stage05_map.bmp");
		spriteManager->LoadSpriteImage(eSpriteType::CutScene01_01, L".\\resources\\image\\cutScene2_1.bmp");
		spriteManager->LoadSpriteImage(eSpriteType::CutScene01_02, L".\\resources\\image\\cutScene2_2.bmp");
		spriteManager->LoadSpriteImage(eSpriteType::CutScene01_03, L".\\resources\\image\\cutScene2_3.bmp");
		spriteManager->LoadSpriteImage(eSpriteType::CutScene01_04, L".\\resources\\image\\cutScene2_4.bmp");
		spriteManager->LoadSpriteImage(eSpriteType::CutScene02_01, L".\\resources\\image\\cutScene4_1.bmp");
		spriteManager->LoadSpriteImage(eSpriteType::CutScene02_02, L".\\resources\\image\\cutScene4_2.bmp");
		spriteManager->LoadSpriteImage(eSpriteType::CutScene02_03, L".\\resources\\image\\cutScene4_3.bmp");
		spriteManager->LoadSpriteImage(eSpriteType::CutScene02_04, L".\\resources\\image\\cutScene4_4.bmp");
		spriteManager->LoadSpriteImage(eSpriteType::CutScene03_01, L".\\resources\\image\\cutScene5_1.bmp");
		spriteManager->LoadSpriteImage(eSpriteType::CutScene03_02, L".\\resources\\image\\cutScene5_2.bmp");
		spriteManager->LoadSpriteImage(eSpriteType::CutScene03_03, L".\\resources\\image\\cutScene5_3.bmp");
		spriteManager->LoadSpriteImage(eSpriteType::CutScene03_04, L".\\resources\\image\\cutScene5_4.bmp");
		spriteManager->LoadSpriteImage(eSpriteType::CutScene03_05, L".\\resources\\image\\cutScene5_5.bmp");
		spriteManager->LoadSpriteImage(eSpriteType::StageClear, L".\\resources\\image\\stage_clear.bmp");
		spriteManager->LoadSpriteImage(eSpriteType::RotateCount, L".\\resources\\image\\rotate_count.bmp");
		spriteManager->LoadSpriteImage(eSpriteType::StageName1, L".\\resources\\image\\StageTitle01.bmp");
		spriteManager->LoadSpriteImage(eSpriteType::StageName2, L".\\resources\\image\\StageTitle02.bmp");
		spriteManager->LoadSpriteImage(eSpriteType::StageName3, L".\\resources\\image\\StageTitle03.bmp");
		spriteManager->LoadSpriteImage(eSpriteType::StageName4, L".\\resources\\image\\StageTitle04.bmp");
		spriteManager->LoadSpriteImage(eSpriteType::StageName5, L".\\resources\\image\\StageTitle05.bmp");
		spriteManager->LoadSpriteImage(eSpriteType::StageName6, L".\\resources\\image\\StageTitle06.bmp");
		spriteManager->LoadSpriteImage(eSpriteType::StageName7, L".\\resources\\image\\StageTitle07.bmp");
		spriteManager->LoadSpriteImage(eSpriteType::StageName8, L".\\resources\\image\\StageTitle08.bmp");
		spriteManager->LoadSpriteImage(eSpriteType::StageName9, L".\\resources\\image\\StageTitle09.bmp");
		spriteManager->LoadSpriteImage(eSpriteType::StageName10, L".\\resources\\image\\StageTitle10.bmp");
		spriteManager->LoadSpriteImage(eSpriteType::SoundOn, L".\\resources\\image\\SoundOn.bmp");
		spriteManager->LoadSpriteImage(eSpriteType::SoundOff, L".\\resources\\image\\SoundOff.bmp");
		spriteManager->LoadSpriteImage(eSpriteType::Home, L".\\resources\\image\\Home.bmp");
		spriteManager->LoadSpriteImage(eSpriteType::EnterButton, L".\\resources\\image\\enter_button.bmp");
		spriteManager->LoadSpriteImage(eSpriteType::ExitButton, L".\\resources\\image\\exit_button.bmp");
		spriteManager->LoadSpriteImage(eSpriteType::ButtonA, L".\\resources\\image\\AKey.bmp");
		spriteManager->LoadSpriteImage(eSpriteType::ButtonD, L".\\resources\\image\\DKey.bmp");
		spriteManager->LoadSpriteImage(eSpriteType::ButtonQ, L".\\resources\\image\\QKey.bmp");
		spriteManager->LoadSpriteImage(eSpriteType::ButtonE, L".\\resources\\image\\EKey.bmp");
		spriteManager->LoadSpriteImage(eSpriteType::ButtonW, L".\\resources\\image\\WKey.bmp");
		spriteManager->LoadSpriteImage(eSpriteType::SpaceButton, L".\\resources\\image\\SpaceButton.bmp");
		spriteManager->LoadSpriteImage(eSpriteType::RotateCountNumber0, L".\\resources\\image\\Rotate0.bmp");
		spriteManager->LoadSpriteImage(eSpriteType::RotateCountNumber1, L".\\resources\\image\\Rotate1.bmp");
		spriteManager->LoadSpriteImage(eSpriteType::RotateCountNumber2, L".\\resources\\image\\Rotate2.bmp");
		spriteManager->LoadSpriteImage(eSpriteType::RotateCountNumber3, L".\\resources\\image\\Rotate3.bmp");
		spriteManager->LoadSpriteImage(eSpriteType::RotateCountNumber4, L".\\resources\\image\\Rotate4.bmp");
		spriteManager->LoadSpriteImage(eSpriteType::RotateCountNumber5, L".\\resources\\image\\Rotate5.bmp");
		spriteManager->LoadSpriteImage(eSpriteType::RotateCountNumber6, L".\\resources\\image\\Rotate6.bmp");
		spriteManager->LoadSpriteImage(eSpriteType::RotateCountNumber7, L".\\resources\\image\\Rotate7.bmp");
		spriteManager->LoadSpriteImage(eSpriteType::Guide11, L".\\resources\\image\\1-1stage.bmp");
		spriteManager->LoadSpriteImage(eSpriteType::Guide12, L".\\resources\\image\\1-2stage.bmp");
		spriteManager->LoadSpriteImage(eSpriteType::Guide21, L".\\resources\\image\\2-1stage.bmp");
		spriteManager->LoadSpriteImage(eSpriteType::Guide31, L".\\resources\\image\\3-1stage.bmp");
		spriteManager->LoadSpriteImage(eSpriteType::Guide41, L".\\resources\\image\\4-1stage.bmp");
		spriteManager->LoadSpriteImage(eSpriteType::Guide51, L".\\resources\\image\\5-1stage.bmp");
		spriteManager->LoadSpriteImage(eSpriteType::Guide52, L".\\resources\\image\\5-2stage.bmp");
	}

	void EnumLoader::LoadAnimationRectangle(SpriteManager* const spriteManager)
	{
		assert(spriteManager != nullptr);

		spriteManager->LoadAnimationRectangle(eAnimationType::PlayerIdle, L".\\resources\\coordinate\\player_idle.txt", PLAYER_IDLE_INTERVAL);
		spriteManager->LoadAnimationRectangle(eAnimationType::PlayerMove, L".\\resources\\coordinate\\player_move.txt", PLAYER_MOVE_INTERVAL);
		spriteManager->LoadAnimationRectangle(eAnimationType::PlayerPlummet, L".\\resources\\coordinate\\player_plummet.txt", PLAYER_PlUMMET_INTERVAL);
		spriteManager->LoadAnimationRectangle(eAnimationType::PlayerAction, L".\\resources\\coordinate\\player_action.txt", PLAYER_ACTION_INTERVAL);
		spriteManager->LoadAnimationRectangle(eAnimationType::RedButterfly, L".\\resources\\coordinate\\RedButterfly.txt", BUTTERPLY_IDLE_INTERVAL);
		spriteManager->LoadAnimationRectangle(eAnimationType::BlueButterfly, L".\\resources\\coordinate\\BlueButterfly.txt", BUTTERPLY_IDLE_INTERVAL);
		spriteManager->LoadAnimationRectangle(eAnimationType::YellowButterfly, L".\\resources\\coordinate\\YellowButterfly.txt", BUTTERPLY_IDLE_INTERVAL);
	}

	void EnumLoader::LoadSound(SoundManager* const soundManager)
	{
		assert(soundManager != nullptr);

		soundManager->LoadMusic(eSoundList::StartBGM, true, ".\\resources\\music\\Main.ogg");
		soundManager->LoadMusic(eSoundList::Stage12BGM, true, ".\\resources\\music\\Stage12.ogg");
		soundManager->LoadMusic(eSoundList::Stage345BGM, true, ".\\resources\\music\\Stage345.ogg");
		soundManager->LoadMusic(eSoundList::CatDropEffect, false, ".\\resources\\music\\Cat_Drop.ogg");
		soundManager->LoadMusic(eSoundList::CatGoalEffect, false, ".\\resources\\music\\Cat_Goal.ogg");
	}

	void EnumLoader::LoadScene(SceneManager* const sceneManager)
	{
		assert(sceneManager != nullptr);

		SceneLoader::Load(sceneManager);
	}
}