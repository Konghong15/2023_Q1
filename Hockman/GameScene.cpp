#include "GameScene.h"
#include "Player.h"
#include "Enemy.h"
#include "Collider.h"
#include "ColliderManager.h"
#include "hRectangle.h"
#include "PlayerState.h"
#include "Ground.h"

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

		obj = new Player(hRectangle(900, 500, 100, 100), hRectangle(37, 40, 21, 24), eSpriteType::Player, eObjectType::PLAYER, 1000.f);
		collider = new Collider(hRectangle(30, 20, 40, 80), *obj);
		obj->AddCollider(collider);

		mSpawnObjects.push_back(obj);
		ColliderManager::GetInstance()->OnRegister(collider);

		obj = new Enemy(hRectangle(900, 500, 100, 100), eSpriteType::Player, 500.f);
		collider = new Collider(hRectangle(10, 10, 80, 80), *obj);
		obj->AddCollider(collider);

		mSpawnObjects.push_back(obj);
		ColliderManager::GetInstance()->OnRegister(collider);

		obj = new Ground(hRectangle(1200, 600, 100, 100), eSpriteType::Player);
		collider = new Collider(hRectangle(0, 0, 100, 100), *obj);
		obj->AddCollider(collider);

		mSpawnObjects.push_back(obj);
		ColliderManager::GetInstance()->OnRegister(collider);

		obj = new Ground(hRectangle(600, 600, 100, 200), eSpriteType::Player);
		collider = new Collider(hRectangle(0, 0, 100, 200), *obj);
		obj->AddCollider(collider);

		mSpawnObjects.push_back(obj);
		ColliderManager::GetInstance()->OnRegister(collider);

		obj = new Ground(hRectangle(0, 800, 1920, 100), eSpriteType::Player);
		collider = new Collider(hRectangle(0, 0, 1920, 100), *obj);
		obj->AddCollider(collider);

		mSpawnObjects.push_back(obj);
		ColliderManager::GetInstance()->OnRegister(collider);

		obj = new Ground(hRectangle(0, 0, 100, 800), eSpriteType::Player);
		collider = new Collider(hRectangle(0, 0, 100, 800), *obj);
		obj->AddCollider(collider);

		mSpawnObjects.push_back(obj);
		ColliderManager::GetInstance()->OnRegister(collider);

		obj = new Ground(hRectangle(1820, 0, 100, 800), eSpriteType::Player);
		collider = new Collider(hRectangle(0, 0, 100, 800), *obj);
		obj->AddCollider(collider);

		mSpawnObjects.push_back(obj);
		ColliderManager::GetInstance()->OnRegister(collider);
	}
}