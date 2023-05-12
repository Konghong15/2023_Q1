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
		if (InputManager::GetInstance()->GetKeyState('X') == eKeyState::POP)
		{
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
			Vector2 size(10 + 10 * mKeyElapsedTime, 10 + 10 * mKeyElapsedTime);
			Vector2 pos;
			Vector2 direction;

			if (player->GetIsRight())
			{
				pos = player->GetRectangle().GetTopRight();
				direction = Vector2(1, 0);
			}
			else
			{
				pos = player->GetRectangle().GetTopLeft();
				direction = Vector2(-1, 0);
			}
			pos.SetY(pos.GetY() + 50);

			Object* obj = new Projectile(hRectangle(pos, size), eSpriteType::Projectile, direction, 1000, 100, 5.f);
			Collider* collider = new Collider(hRectangle(Vector2(0, 0), size), *obj);
			obj->AddCollider(collider);

			ColliderManager::GetInstance()->OnRegister(collider);
			SceneManager::GetInstance()->SpawnCurScene(obj);
		}
	}
}