#pragma once

#include <Windows.h>
#include <vector>

namespace hongpireSurvivors
{
	class Object;

	class ObjectManager
	{
	public:
		static ObjectManager* GetInstance();
		static void DeleteInstance();

		void Frame();

		inline void OnSpawn(Object* object);

	private:
		ObjectManager();
		~ObjectManager() = default;

	private:
		static ObjectManager* mInstance;

		std::vector<Object*> mObjects;
		std::vector<Object*> mDeadObjects;
	};

	void ObjectManager::OnSpawn(Object* object)
	{
		mObjects.push_back(object);
	}
}