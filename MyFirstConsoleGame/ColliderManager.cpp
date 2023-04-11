#pragma once

#include "ColliderManager.h"
#include "Object.h"

namespace hongpireSurvivors
{
	ColliderManager* ColliderManager::mInstance = nullptr;

	ColliderManager* ColliderManager::GetInstance()
	{
		if (mInstance == nullptr)
		{
			mInstance = new ColliderManager();
		}

		return mInstance;
	}

	void ColliderManager::DeleteInstance()
	{
		delete mInstance;
		mInstance = nullptr;
	}

	ColliderManager::ColliderManager()
	{
		mColliders.reserve(128);
	}

	void ColliderManager::Frame()
	{
		for (auto iter = mColliders.begin(); iter != mColliders.end();)
		{
			if (!(*iter)->GetOwnerObject().GetValid())
			{
				iter = mColliders.erase(iter);
			}
			else
			{
				(*iter)->InitEnter();
				++iter;
			}
		}

		for (auto iterI = mColliders.begin(); iterI != mColliders.end(); ++iterI)
		{
			for (auto IterJ = iterI + 1; IterJ != mColliders.end(); ++IterJ)
			{
				if ((*iterI)->GetOwnerObject().GetValid() && (*IterJ)->GetOwnerObject().GetValid())
				{
					(*iterI)->CheckCollision(**IterJ);
				}
			}
		}

		for (auto iter = mColliders.begin(); iter != mColliders.end(); ++iter)
		{
			(*iter)->CheckExitCollision();
		}
	}
};
