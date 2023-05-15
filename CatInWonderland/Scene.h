#pragma once

#include <cassert>
#include <vector>

namespace catInWonderland
{
	class Object;

	class Scene
	{
	public:
		Scene();
		virtual ~Scene() = default;

		virtual void Enter() = 0;
		virtual void Frame();
		virtual void Render();
		virtual void Exit();

		inline void Spawn(Object* obj);

	protected:
		enum { RESERVE_SIZE = 128 };

		std::vector<Object*> mObjects;
		std::vector<Object*> mDeadObjects;
		std::vector<Object*> mSpawnObjects;
	};

	void Scene::Spawn(Object* obj)
	{
		assert(obj != nullptr);
		mSpawnObjects.push_back(obj);
	}
}