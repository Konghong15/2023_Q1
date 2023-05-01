#pragma once

#include <vector>

namespace hongpireSurvivors
{
	class Object;
	class Player;

	class ObjectManager
	{
	public:
		static ObjectManager* GetInstance();
		static void DeleteInstance();

		void Init();
		void Frame();
		void Release();

		void RegisterPlayer(Player* player);
		inline void OnSpawn(Object* object);

		inline Object* GetPlayerOrNull() const;
		inline int GetObjectCount() const;

	private:
		ObjectManager() = default;
		~ObjectManager() = default;

	private:
		enum { RESERVE_SIZE = 128 };

		static ObjectManager* mInstance;

		Object* mPlayer;
		std::vector<Object*> mObjects;
		std::vector<Object*> mDeadObjects;
		std::vector<Object*> mSpawnObjects;
	};

	void ObjectManager::OnSpawn(Object* object)
	{
		mSpawnObjects.push_back(object);
	}

	Object* ObjectManager::GetPlayerOrNull() const
	{
		return mPlayer;
	}

	int ObjectManager::GetObjectCount() const
	{
		return mObjects.size();
	}
}