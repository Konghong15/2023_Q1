#pragma once

#include <Windows.h>
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

		void Frame();

		inline void RegisterPlayer(Player* player);
		inline void OnSpawn(Object* object);
		inline const Object& GetPlayer() const;

	private:
		ObjectManager();
		~ObjectManager() = default;

	private:
		static ObjectManager* mInstance;

		Player* mPlayer;
		std::vector<Object*> mObjects;
		std::vector<Object*> mDeadObjects;
	};

	void ObjectManager::OnSpawn(Object* object)
	{
		mObjects.push_back(object);
	}

	void ObjectManager::RegisterPlayer(Player* player)
	{
		if (mPlayer == nullptr)
		{
			mPlayer = player;
		}
	}

	const Object& ObjectManager::GetPlayer() const
	{
		return *((Object*)mPlayer);
	}
}