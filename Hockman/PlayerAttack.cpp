#include "PlayerAttack.h"
#include "PlayerNonAttack.h"
#include "TimeManager.h"
#include "SceneManager.h"
#include "Projectile.h"
#include "Collider.h"
#include "ColliderManager.h"
#include "Player.h"

namespace hockman
{
	PlayerAttack::PlayerAttack()
		: PlayerState(ePlayerState::Attack)
		, mAttackInterval(0.2f)
	{
	}

	void PlayerAttack::Enter(Player* player)
	{
		player->SetAniIndexY(1);

		Vector2 size(10, 10);
		Vector2 pos;
		Vector2 direction;

		if (player->GetIsRight())
		{
			pos = player->GetRectangle().GetTopRight();
			direction = Vector2(1, 0);
		}
		else
		{
			pos = player->GetRectangle().GetPos();
			direction = Vector2(-1, 0);
		}
		pos.SetY(pos.GetY() + 50);

		Object* obj = new Projectile(hRectangle(pos, size), eSpriteType::Projectile, direction, 1500, 0, 5.f);
		Collider* collider = new Collider(hRectangle(Vector2(0, 0), size), *obj);
		obj->AddCollider(collider);

		ColliderManager::GetInstance()->OnRegister(collider);
		SceneManager::GetInstance()->SpawnCurScene(obj);
	}

	PlayerState* PlayerAttack::HandleInputOrNull(Player* player)
	{
		if (mAttackInterval < 0.f)
		{
			player->SetAniIndexY(0);

			return new PlayerNonAttack();
		}

		return nullptr;
	}

	void PlayerAttack::Update(Player* player)
	{
		const float DELTA_TIME = TimeManager::GetInstance()->GetDeltaTime();

		mAttackInterval -= DELTA_TIME;
	}
}