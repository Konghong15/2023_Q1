#pragma once

#include <vector>

namespace hockman
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

		inline void Spawn(Object* object);

	private:
		ObjectManager() = default;
		~ObjectManager() = default;

	private:
		enum { RESERVE_SIZE = 128 };

		static ObjectManager* mInstance;

		std::vector<Object*> mObjects;
		std::vector<Object*> mDeadObjects;
		std::vector<Object*> mSpawnObjects;
	};

	void ObjectManager::Spawn(Object* object)
	{
		mSpawnObjects.push_back(object);
	}
}