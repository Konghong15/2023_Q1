#pragma once

#include <cassert>
#include <vector>

namespace hockman
{
	class Object;

	class Scene
	{
	public:
		Scene(size_t width, size_t height);
		virtual ~Scene() = default;

		virtual void Enter();
		virtual void Frame();
		virtual void Exit();

		inline size_t GetWidth() const;
		inline size_t GetHeight() const;

		inline void Spawn(Object* obj);

	protected:
		enum { RESERVE_SIZE = 128 };

		size_t mWidth;
		size_t mHeight;

		std::vector<Object*> mObjects;
		std::vector<Object*> mDeadObjects;
		std::vector<Object*> mSpawnObjects;
	};

	size_t Scene::GetWidth() const
	{
		return mWidth;
	}

	size_t Scene::GetHeight() const
	{
		return mHeight;
	}

	void Scene::Spawn(Object* obj)
	{
		assert(obj != nullptr);
		mSpawnObjects.push_back(obj);
	}
}