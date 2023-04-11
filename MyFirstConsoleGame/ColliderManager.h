#pragma once

#include <vector>

#include "Collider.h"

namespace hongpireSurvivors
{
	class ColliderManager
	{
	public:
		static ColliderManager* GetInstance();
		static void DeleteInstance();

		void Frame();

		inline void OnRegister(Collider* collider);

	private:
		ColliderManager();
		~ColliderManager() = default;

	private:
		static ColliderManager* mInstance;

		std::vector<Collider*> mColliders; // 삭제 책임은 Object가 지도록 처리
	};

	void ColliderManager::OnRegister(Collider* collider)
	{
		mColliders.push_back(collider);
	}
}