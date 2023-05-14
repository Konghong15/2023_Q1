#include "PlayerCharging.h"
#include "PlayerNonAttack.h"
#include "TimeManager.h"
#include "InputManager.h"
#include "Projectile.h"
#include "Collider.h"
#include "SceneManager.h"
#include "ColliderManager.h"
#include "Player.h"

namespace hockman
{
	PlayerCharging::PlayerCharging()
		: PlayerState(ePlayerState::Charging)
		, mKeyElapsedTime(0.f)
		, mAniElpased(0.f)
		, mAttackInterval(0.2f)
		, mIsShoot(false)
	{
	}

	void PlayerCharging::Enter(Player* player)
	{

	}

	PlayerState* PlayerCharging::HandleInputOrNull(Player* player)
	{
		if (mAttackInterval < 0.f)
		{
			player->SetAniIndexY(0);
			return new PlayerNonAttack();
		}

		return nullptr;
	}

	void PlayerCharging::Update(Player* player)
	{
		const float DELTA_TIME = TimeManager::GetInstance()->GetDeltaTime();
		mKeyElapsedTime += DELTA_TIME;
		mAniElpased += DELTA_TIME;

		if (mIsShoot)
		{
			mAttackInterval -= DELTA_TIME;
			return;
		}

		if (mKeyElapsedTime > 3.f)
		{
			mKeyElapsedTime = 3.f;
		}
		if (mAniElpased > 0.05f)
		{
			mAniElpased = 0.f;
			player->AddAniIndexY();

			if (player->GetAniIndexY() == 1)
			{
				player->AddAniIndexY();
			}
		}

		if (InputManager::GetInstance()->GetKeyState('X') == eKeyState::POP)
		{
			player->SetAniIndexY(1);
			mIsShoot = true;
			Vector2 topLeft;
			Vector2 bottomRight;
			Vector2 direction;

			if (player->GetIsRight())
			{
				topLeft = player->GetRectangle().GetTopRight();
				topLeft += Vector2(0, 50);
				bottomRight = topLeft + Vector2(20, 20);
				direction = Vector2(1, 0);
			}
			else
			{
				topLeft = player->GetRectangle().GetTopRight();
				topLeft += Vector2(-20, 50);
				bottomRight = topLeft + Vector2(20, 20);
				direction = Vector2(-1, 0);
			}

			Object* obj = new Projectile(hRectangle(topLeft, bottomRight), eSpriteType::Projectile, direction, 1500, 0, 5.f);
			Collider* collider = new Collider(hRectangle(0, 0, 0, 0), *obj);
			obj->AddCollider(collider);

			ColliderManager::GetInstance()->OnRegister(collider);
			SceneManager::GetInstance()->SpawnCurScene(obj);
		}
	}
}