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

int main(void)
{
	using namespace hongpireSurvivors;

	// ground 67
	// max x 400

	TimeManager::GetInstance();
	InputManager::GetInstance();
	ObjectManager::GetInstance();
	ColliderManager::GetInstance();
	RenderManager::GetInstance();
	SpriteManager::GetInstance();

	Player* player = new Player({ 40, 52 }, { 15, 15 }, eSpriteType::PLAYER_IDLE);
	Monster* monster = new Monster({ 80, 53 }, { 15, 15 }, eSpriteType::MONSTER_LEFT);

	ObjectManager::GetInstance()->OnSpawn(player);
	ObjectManager::GetInstance()->OnSpawn(monster);
	Collider* col1 = new Collider({ 15, 15 }, { 0, 0 }, *player);
	Collider* col2 = new Collider({ 15, 15 }, { 0, 0 }, *monster);
	player->AddCollider(col1);
	monster->AddCollider(col2);
	ColliderManager::GetInstance()->OnRegister(col1);
	ColliderManager::GetInstance()->OnRegister(col2);


	while (true)
	{
		TimeManager::GetInstance()->Frame();
		InputManager::GetInstance()->Frame();

		ObjectManager::GetInstance()->Frame();
		ColliderManager::GetInstance()->Frame();

		RenderManager::GetInstance()->Render();
	}

	SpriteManager::DeleteInstance();
	RenderManager::DeleteInstance();
	ColliderManager::DeleteInstance();
	ObjectManager::DeleteInstance();
	InputManager::DeleteInstance();
	TimeManager::DeleteInstance();
}