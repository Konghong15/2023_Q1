#define _CRT_SECURE_NO_WARNINGS

#include <fstream>
#include <string>

#include "RenderManager.h"
#include "TimeManager.h"
#include "InputManager.h"
#include "ObjectManager.h"
#include "SpriteManager.h"
#include "eSpriteType.h"

#include "Player.h"

int main(void)
{
	using namespace hongpireSurvivors;

	RenderManager::GetInstance();
	TimeManager::GetInstance();
	InputManager::GetInstance();
	ObjectManager::GetInstance();
	SpriteManager::GetInstance();

	Player player({ 40, 40 }, { 30, 30 }, eSpriteType::PLAYER_IDLE);

	ObjectManager::GetInstance()->OnSpawn(&player);

	while (true)
	{
		ObjectManager::GetInstance()->Frame();
		TimeManager::GetInstance()->Frame();
		InputManager::GetInstance()->Frame();
		RenderManager::GetInstance()->Render();
	}

	RenderManager::GetInstance()->DeleteInstance();
	TimeManager::GetInstance()->DeleteInstance();
	InputManager::GetInstance()->DeleteInstance();
}