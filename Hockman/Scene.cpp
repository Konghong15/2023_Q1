#include "Scene.h"
#include "Object.h"

namespace hockman
{
	Scene::Scene(size_t width, size_t height)
		: mWidth(width)
		, mHeight(height)
	{
	}

	void Scene::Enter()
	{
		mObjects.reserve(RESERVE_SIZE);
		mDeadObjects.reserve(RESERVE_SIZE);
		mSpawnObjects.reserve(RESERVE_SIZE);
	}

	void Scene::Frame()
	{
		for (auto iter = mDeadObjects.begin(); iter != mDeadObjects.end(); ++iter)
		{
			Object* obj = (*iter);
			delete obj;
		}
		mDeadObjects.clear();

		for (auto iter = mSpawnObjects.begin(); iter != mSpawnObjects.end(); ++iter)
		{
			mObjects.push_back((*iter));
		}
		mSpawnObjects.clear();

		for (auto iter = mObjects.begin(); iter != mObjects.end();)
		{
			(*iter)->Frame();

			if (!(*iter)->GetValid())
			{
				mDeadObjects.push_back(*iter);
				iter = mObjects.erase(iter);
			}
			else
			{
				++iter;
			}
		}

		for (auto iter = mObjects.begin(); iter != mObjects.end(); ++iter)
		{
			(*iter)->Render();
		}

	}

	void Scene::Exit()
	{
		for (auto iter = mDeadObjects.begin(); iter != mDeadObjects.end(); ++iter)
		{
			Object* obj = (*iter);
			delete obj;
		}
		mDeadObjects.clear();

		for (auto iter = mSpawnObjects.begin(); iter != mSpawnObjects.end(); ++iter)
		{
			Object* obj = (*iter);
			delete obj;
		}
		mSpawnObjects.clear();

		for (auto iter = mObjects.begin(); iter != mObjects.end(); ++iter)
		{
			Object* obj = (*iter);
			delete obj;
		}
		mObjects.clear();
	}
}