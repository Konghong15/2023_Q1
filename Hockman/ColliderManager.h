#pragma once

namespace hockman
{
	class Collider;

	class ColliderManager
	{
	public:
		static ColliderManager* GetInstance();
		static void DeleteInstance();

		void Init();
		void Frame();
		void Release();

		inline void OnRegister(Collider* collider);

	private:
		ColliderManager() = default;
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