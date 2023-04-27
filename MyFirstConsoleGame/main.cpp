#define _CRT_SECURE_NO_WARNINGS

#include <fstream>
#include <string>

#include "RenderManager.h"
#include "TimeManager.h"
#include "InputManager.h"
#include "ObjectManager.h"
#include "SpriteManager.h"
#include "eSpriteType.h"
#include "ColliderManager.h"

#include "Collider.h"
#include "Player.h"
#include "Monster.h"
#include "Zombie.h"
#include "Bat.h"
#include "Devil.h"
#include "Orge.h"
#include "FlyingOrge.h"
#include "KingOrge.h"
#include "Helper.h"
#include "Scene.h"

#pragma comment(lib, "./fmod/fmod_vc.lib")
#pragma comment(lib, "./fmod/fmodL_vc.lib")
using namespace hongpireSurvivors;

/*
	ENEMY_0, // 15 17
	ENEMY_1, // 20 13
	ENEMY_2, // 20 8
	BOSS_0_IDLE, // 30 29
	BOSS_0_JUMP, // 30 28
	BOSS_1_IDLE, // 30 26
	BOSS_1_ATTACK, // 30 23
	BOSS_2_IDLE, // 35 33
	BOSS_2_ATTACK, // 35 31
	BOSS_2_PROJECTILE, // 15 8
*/

//void handle_monster(void)
//{
//	if (InputManager::GetInstance()->GetKeyState(VK_F1) == eKeyState::PUSH)
//	{
//		Zombie* monster = new Zombie({ 300, 67 - 17 }, { 15, 17 }, eSpriteType::ENEMY_0);
//		Helper::Spawn(monster, 15, 17);
//	}
//	if (InputManager::GetInstance()->GetKeyState(VK_F2) == eKeyState::PUSH)
//	{
//		Bat* monster = new Bat({ 300, 67 - 20 - 20 }, { 20, 8 }, eSpriteType::ENEMY_2);
//		Helper::Spawn(monster, 20, 13);
//	}
//	if (InputManager::GetInstance()->GetKeyState(VK_F3) == eKeyState::PUSH)
//	{
//		Devil* monster = new Devil({ 300, 67 - 20 - 20 }, { 20, 13 });
//		Helper::Spawn(monster, 20, 13);
//	}
//	if (InputManager::GetInstance()->GetKeyState(VK_F4) == eKeyState::PUSH)
//	{
//		Orge* monster = new Orge({ 300, 67 - 29 }, { 30, 29 });
//		Helper::Spawn(monster, 30, 29);
//	}
//	if (InputManager::GetInstance()->GetKeyState(VK_F5) == eKeyState::PUSH)
//	{
//		FlyingOrge* monster = new FlyingOrge({ 300, 3 }, { 30, 26 });
//		Helper::Spawn(monster, 30, 26);
//	}
//	if (InputManager::GetInstance()->GetKeyState(VK_F6) == eKeyState::PUSH)
//	{
//		KingOrge* monster = new KingOrge({ 300, 67 - 33 }, { 35, 33 });
//		Helper::Spawn(monster, 35, 33);
//	}
//}

int main(void)
{
	eSpriteType map[4] = { eSpriteType::MAP_1_0, eSpriteType::MAP_1_1, eSpriteType::MAP_1_2, eSpriteType::MAP_2_0 };

	// ground 67
	// max x 400

	TimeManager::GetInstance()->Init();
	InputManager::GetInstance();
	ObjectManager::GetInstance();
	ColliderManager::GetInstance();
	RenderManager::GetInstance();
	SpriteManager::GetInstance();
	Scene::mScene = new Scene({ (SHORT)1600, (SHORT)79 }, map, 4u, { (SHORT)400, (SHORT)79 });

	//spawn(eSpriteType::ENEMY_1, 85, 67 - 13, 20, 13);
	//spawn(eSpriteType::ENEMY_2, 115, 67 - 8, 20, 8);
	//spawn(eSpriteType::BOSS_0_IDLE, 145, 67 - 29, 30, 29);
	//spawn(eSpriteType::BOSS_1_IDLE, 185, 67 - 26, 30, 26);
	//spawn(eSpriteType::BOSS_2_IDLE, 230, 67 - 33, 35, 33);

	while (true)
	{
		TimeManager::GetInstance()->Frame();
		InputManager::GetInstance()->Frame();

		Scene::mScene->Frame();
		ColliderManager::GetInstance()->Frame();
		ObjectManager::GetInstance()->Frame();

		RenderManager::GetInstance()->Render();
	}

	SpriteManager::DeleteInstance();
	RenderManager::DeleteInstance();
	ColliderManager::DeleteInstance();
	ObjectManager::DeleteInstance();
	InputManager::DeleteInstance();
	TimeManager::DeleteInstance();
}