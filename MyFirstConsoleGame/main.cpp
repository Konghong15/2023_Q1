#define _CRT_SECURE_NO_WARNINGS

#include "TimeManager.h"
#include "InputManager.h"
#include "ObjectManager.h"
#include "SceneManager.h"
#include "RenderManager.h"
#include "ColliderManager.h"

#include "eSceneType.h"
#include "eSpriteType.h"
#include "TitleScene.h"
#include "GameScene.h"

#pragma comment(lib, "./fmod/fmod_vc.lib")
#pragma comment(lib, "./fmod/fmodL_vc.lib")
using namespace hongpireSurvivors;

int main(void)
{
	TimeManager::GetInstance()->Init();
	InputManager::GetInstance();
	ObjectManager::GetInstance()->Init();
	SceneManager::GetInstance()->OnRegister(eSceneType::TITLE, new TitleScene(eSpriteType::TITLE_BG_0, { 400, 65 }));
	SceneManager::GetInstance()->OnRegister(eSceneType::GAME, new GameScene(eSpriteType::GAME_BG, { 1599, 79 }));
	RenderManager::GetInstance();
	SceneManager::GetInstance()->Init();
	ColliderManager::GetInstance();

	while (true)
	{
		TimeManager::GetInstance()->Frame();
		InputManager::GetInstance()->Frame();
		ColliderManager::GetInstance()->Frame();

		SceneManager::GetInstance()->Frame();
		ObjectManager::GetInstance()->Frame();
		RenderManager::GetInstance()->Render();
	}

	ColliderManager::DeleteInstance();
	RenderManager::GetInstance()->DeleteInstance();
	SceneManager::DeleteInstance();
	ObjectManager::DeleteInstance();
	InputManager::DeleteInstance();
	TimeManager::DeleteInstance();
}