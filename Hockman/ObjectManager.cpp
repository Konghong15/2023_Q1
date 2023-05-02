#include <Windows.h>
#include <vector>

#include "ObjectManager.h"
#include "Object.h"

namespace hockman
{
	ObjectManager* ObjectManager::mInstance = nullptr;

	ObjectManager* ObjectManager::GetInstance()
	{
		if (mInstance == nullptr)
		{
			mInstance = new ObjectManager();
		}

		return mInstance;
	}

	void ObjectManager::DeleteInstance()
	{
		delete mInstance;
		mInstance = nullptr;
	}

	void ObjectManager::Init()
	{
		mObjects.reserve(RESERVE_SIZE);
		mDeadObjects.reserve(RESERVE_SIZE);
		mSpawnObjects.reserve(RESERVE_SIZE);
	}

	void ObjectManager::Frame()
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

	void ObjectManager::Release()
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