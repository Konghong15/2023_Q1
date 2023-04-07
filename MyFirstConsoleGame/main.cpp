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
#include "Helper.h"

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

void handle_monster(void)
{
	if (InputManager::GetInstance()->GetKeyState(VK_F1) == eKeyState::PUSH)
	{
		Zombie* monster = new Zombie({ 300, 67 - 17 }, { 15, 17 }, eSpriteType::ENEMY_0);
		Helper::Spawn(monster, 300, 67 - 17, 15, 17);
	}
	if (InputManager::GetInstance()->GetKeyState(VK_F2) == eKeyState::PUSH)
	{
		Bat* monster = new Bat({ 300, 67 - 20 - 20 }, { 20, 8 }, eSpriteType::ENEMY_2);
		Helper::Spawn(monster, 300, 67 - 20 - 20, 20, 13);
	}
	if (InputManager::GetInstance()->GetKeyState(VK_F3) == eKeyState::PUSH)
	{
		Devil* monster = new Devil({ 300, 67 - 20 - 20 }, { 20, 13 });
		Helper::Spawn(monster, 300, 67 - 20 - 20, 20, 13);
	}
	if (InputManager::GetInstance()->GetKeyState(VK_F4) == eKeyState::PUSH)
	{
		Orge* monster = new Orge({ 300, 67 - 29 }, { 30, 29 });
		Helper::Spawn(monster, 300, 67 - 29, 30, 29);
	}
	if (InputManager::GetInstance()->GetKeyState(VK_NUMPAD5) == eKeyState::PUSH)
	{

	}
	if (InputManager::GetInstance()->GetKeyState(VK_NUMPAD6) == eKeyState::PUSH)
	{

	}
}

int main(void)
{
	// ground 67
	// max x 400

	TimeManager::GetInstance()->Init();
	InputManager::GetInstance();
	ObjectManager::GetInstance();
	ColliderManager::GetInstance();
	RenderManager::GetInstance();
	SpriteManager::GetInstance();

	Player* player = new Player({ 40, 52 }, { 15, 15 }, eSpriteType::PLAYER_IDLE);
	ObjectManager::GetInstance()->OnSpawn(player);
	ObjectManager::GetInstance()->RegisterPlayer(player);
	Collider* col1 = new Collider({ 15, 15 }, { 0, 0 }, *player);
	player->AddCollider(col1);
	ColliderManager::GetInstance()->OnRegister(col1);

	//spawn(eSpriteType::ENEMY_1, 85, 67 - 13, 20, 13);
	//spawn(eSpriteType::ENEMY_2, 115, 67 - 8, 20, 8);
	//spawn(eSpriteType::BOSS_0_IDLE, 145, 67 - 29, 30, 29);
	//spawn(eSpriteType::BOSS_1_IDLE, 185, 67 - 26, 30, 26);
	//spawn(eSpriteType::BOSS_2_IDLE, 230, 67 - 33, 35, 33);

	float deltaTime = 6.0f;
	while (true)
	{
		deltaTime += TimeManager::GetInstance()->GetDeltaTime();
		if (deltaTime > 5.f)
		{
			deltaTime = 0.f;
		}

		TimeManager::GetInstance()->Frame();
		InputManager::GetInstance()->Frame();

		ObjectManager::GetInstance()->Frame();
		ColliderManager::GetInstance()->Frame();

		RenderManager::GetInstance()->Render();
		handle_monster();
	}

	SpriteManager::DeleteInstance();
	RenderManager::DeleteInstance();
	ColliderManager::DeleteInstance();
	ObjectManager::DeleteInstance();
	InputManager::DeleteInstance();
	TimeManager::DeleteInstance();
}