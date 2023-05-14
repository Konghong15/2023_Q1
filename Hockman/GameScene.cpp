#include "GameScene.h"
#include "Player.h"
#include "Enemy.h"
#include "Collider.h"
#include "ColliderManager.h"
#include "hRectangle.h"
#include "PlayerState.h"
#include "Ground.h"
#include "WinApp.h"

namespace hockman
{
	GameScene::GameScene(size_t width, size_t height)
		: Scene(width, height)
	{
	}

	void GameScene::Enter()
	{
		Scene::Enter();
		Object* obj;
		Collider* collider;

		PlayerState::Init();

		obj = new Player(hRectangle(900, 500, 1000, 600), hRectangle(37, 40, 58, 64), eSpriteType::Player, eObjectType::PLAYER, 1000.f);
		collider = new Collider(hRectangle(20, 20, 20, 0), *obj);
		obj->AddCollider(collider);
		Spawn(obj);
		ColliderManager::GetInstance()->OnRegister(collider);

		obj = new Enemy(hRectangle(900, 500, 100, 100), eSpriteType::Player, 500.f);
		collider = new Collider(hRectangle(0, 0, 0, 0), *obj);
		obj->AddCollider(collider);
		Spawn(obj);
		ColliderManager::GetInstance()->OnRegister(collider);

		const int CENTER_X = WinApp::GetWidth() / 2;
		const int CENTER_Y = WinApp::GetHeight() / 2;
		const int SIDE_LENGTH = 500;
		const int SIDE_WEIGHT = 100;

		obj = new Ground(hRectangle(CENTER_X - SIDE_LENGTH / 2, CENTER_Y - SIDE_LENGTH / 2 - SIDE_WEIGHT, CENTER_X + SIDE_LENGTH / 2, CENTER_Y - SIDE_LENGTH / 2), eSpriteType::Player);
		collider = new Collider(hRectangle(0, 0, 0, 0), *obj);
		obj->AddCollider(collider);
		Spawn(obj);
		ColliderManager::GetInstance()->OnRegister(collider);

		obj = new Ground(hRectangle(CENTER_X + SIDE_LENGTH / 2, CENTER_Y - SIDE_LENGTH / 2, CENTER_X + SIDE_LENGTH / 2 + SIDE_WEIGHT, CENTER_Y + SIDE_LENGTH / 2), eSpriteType::Player);
		collider = new Collider(hRectangle(0, 0, 0, 0), *obj);
		obj->AddCollider(collider);
		Spawn(obj);
		ColliderManager::GetInstance()->OnRegister(collider);

		obj = new Ground(hRectangle(CENTER_X - SIDE_LENGTH / 2, CENTER_Y + SIDE_LENGTH / 2, CENTER_X + SIDE_LENGTH / 2, CENTER_Y + SIDE_LENGTH / 2 + SIDE_WEIGHT), eSpriteType::Player);
		collider = new Collider(hRectangle(0, 0, 0, 0), *obj);
		obj->AddCollider(collider);
		Spawn(obj);
		ColliderManager::GetInstance()->OnRegister(collider);

		obj = new Ground(hRectangle(CENTER_X - SIDE_LENGTH / 2 - SIDE_WEIGHT, CENTER_Y - SIDE_LENGTH / 2, CENTER_X - SIDE_LENGTH / 2, CENTER_Y + SIDE_LENGTH / 2), eSpriteType::Player);
		collider = new Collider(hRectangle(0, 0, 0, 0), *obj);
		obj->AddCollider(collider);
		Spawn(obj);
		ColliderManager::GetInstance()->OnRegister(collider);
	}
}