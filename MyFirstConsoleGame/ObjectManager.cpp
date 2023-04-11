#include "ObjectManager.h"
#include "Object.h"
#include "Player.h"
#include "Helper.h"

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

	ObjectManager::ObjectManager()
		: mObjects()
	{
		mObjects.reserve(128);
		mDeadObjects.reserve(128);
	}

	ObjectManager::~ObjectManager()
	{
		for (auto iter = mDeadObjects.begin(); iter != mDeadObjects.end();)
		{
			Object* obj = (*iter);
			++iter;
			delete obj;
		}
		mDeadObjects.clear();

		for (auto iter = mObjects.begin(); iter != mObjects.end();)
		{
			Object* obj = (*iter);
			++iter;
			delete obj;
		}
		mObjects.clear();
	}

	void ObjectManager::Frame()
	{
		for (auto iter = mDeadObjects.begin(); iter != mDeadObjects.end();)
		{
			Object* obj = (*iter);
			++iter;
			delete obj;
		}
		mDeadObjects.clear();

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
}