#include "ObjectManager.h"
#include "Object.h"
#include "Player.h"

namespace hongpireSurvivors
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

	void ObjectManager::Frame()
	{
		if (!mPlayer->GetValid())
		{
			mPlayer = nullptr;
		}

		for (auto iter = mDeadObjects.begin(); iter != mDeadObjects.end(); ++iter)
		{
			delete* iter;
		}
		mDeadObjects.clear();

		for (auto iter = mObjects.begin(); iter != mObjects.end();)
		{
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
			(*iter)->Frame();
		}
		for (auto iter = mObjects.begin(); iter != mObjects.end(); ++iter)
		{
			(*iter)->Render();
		}
	}

	ObjectManager::ObjectManager()
		: mObjects()
		, mPlayer(nullptr)
	{
		mObjects.reserve(128);
		mDeadObjects.reserve(128);
	}
}