#pragma once

#include <Windows.h>
#include "eSpriteType.h"

namespace hockman
{
	class Player;
	class Object;

	class Scene
	{
	public:
		Scene(COORD sceneSize, COORD camaraPos = { 0,0 });
		virtual ~Scene() = default;

		virtual void Enter() = 0;
		virtual void Frame() = 0;
		virtual void Exit() = 0;

		inline const COORD& GetSceneSize() const;
		inline const COORD& GetCamaraPos() const;

	protected:
		COORD mSceneSize;
		COORD mCamaraPos;
	};

	const COORD& Scene::GetSceneSize() const
	{
		return mSceneSize;
	}

	const COORD& Scene::GetCamaraPos() const
	{
		return mCamaraPos;
	}
}