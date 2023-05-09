#include "GameScene.h"
#include "Player.h"
#include "Enemy.h"
#include "Collider.h"
#include "ColliderManager.h"
#include "hRectangle.h"
#include "PlayerState.h"

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
		collider = new Collider(hRectangle(10, 10, 80, 80), *obj);
		obj->AddCollider(collider);

		mSpawnObjects.push_back(obj);
		ColliderManager::GetInstance()->OnRegister(collider);

		obj = new Enemy(hRectangle(900, 500, 100, 100), eSpriteType::Player, 500.f);
		collider = new Collider(hRectangle(10, 10, 80, 80), *obj);
		obj->AddCollider(collider);

		mSpawnObjects.push_back(obj);
		ColliderManager::GetInstance()->OnRegister(collider);
	}
}