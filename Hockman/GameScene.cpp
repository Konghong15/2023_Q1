#include "GameScene.h"
#include "Player.h"
#include "Enemy.h"
#include "Collider.h"
#include "ColliderManager.h"

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

		obj = new Player(Vector2(900, 500), Vector2(100, 100), Vector2(1, 0), eSpriteType::PLAYER_IDLE, eObjectType::PLAYER, 1000.f);
		collider = new Collider(Vector2(80, 80), Vector2(10, 10), *obj);
		obj->AddCollider(collider);

		mSpawnObjects.push_back(obj);
		ColliderManager::GetInstance()->OnRegister(collider);

		obj = new Enemy(Vector2(900, 500), Vector2(100, 100), Vector2(1, 0), eSpriteType::PLAYER_IDLE, 500.f);
		collider = new Collider(Vector2(80, 80), Vector2(10, 10), *obj);
		obj->AddCollider(collider);

		mSpawnObjects.push_back(obj);
		ColliderManager::GetInstance()->OnRegister(collider);
	}
}