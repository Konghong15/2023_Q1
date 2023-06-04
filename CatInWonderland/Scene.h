#pragma once

#include <vector>

#include "eSceneType.h"

namespace catInWonderland
{
	class Object;
	class Button;

	class Scene
	{
	public:
		Scene(eSceneType sceneType);
		virtual ~Scene();

		virtual eSceneType HandleScene() = 0;
		virtual void Enter();
		virtual void Update();
		virtual void Render();
		virtual void Exit();

		inline void RegisterObject(Object* object);
		inline eSceneType GetSceneType() const;

		inline const std::vector<Object*>& GetObjects() const;

	protected:
		enum { OBJECT_CAPACITY = 256 };
		eSceneType mSceneType;
		std::vector<Object*> mObjects;
		Button* mSoundButton;
		static bool mbSoundOn;

		float mFadeInElapsed;
		bool mbStart;
	};

	void Scene::RegisterObject(Object* object)
	{
		mObjects.push_back(object);
	}

	eSceneType Scene::GetSceneType() const
	{
		return mSceneType;
	}

	const std::vector<Object*>& Scene::GetObjects() const
	{
		return mObjects;
	}
}