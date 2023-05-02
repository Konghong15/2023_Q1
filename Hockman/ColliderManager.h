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

		std::vector<Collider*> mColliders; // ���� å���� Object�� ������ ó��
	};

	void ColliderManager::OnRegister(Collider* collider)
	{
		mColliders.push_back(collider);
	}
}