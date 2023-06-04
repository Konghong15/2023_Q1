#include "CutScene.h"
#include "SpriteManager.h"
#include "ConstantTable.h"
#include "WinApp.h"
#include "RenderManager.h"
#include "Button.h"

namespace catInWonderland
{
	CutScene::CutScene(eSceneType sceneType)
		: Scene(sceneType)
		, mMap(nullptr)
		, mSpaceButton(nullptr)
	{
	}

	void CutScene::Enter()
	{
		mSpaceButton = new Button(SPACE_BUTTON_WORLD_RECT
			, SPACE_BUTTON_RECT
			, &SpriteManager::GetInstance()->GetSprite(eSpriteType::SpaceButton)
			, eLayerType::Background);
		RegisterObject(mSpaceButton);

		Scene::Enter();
	}

	void CutScene::Exit()
	{
		mSpaceButton = nullptr;
		Scene::Exit();
	}

}