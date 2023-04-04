#include "ObjectManager.h"
#include "Object.h"

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
		for (auto iter = mObjects.begin(); iter != mObjects.end(); ++iter)
		{
			// remove unvaild unit
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
	{
		mObjects.reserve(128);
	}
}