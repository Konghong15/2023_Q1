#pragma once

#include <Windows.h>
#include <vector>
#include <map>

#include "BoardObjectInfo.h"
#include "eSceneType.h"

namespace catInWonderland
{
	class SceneManager;

	class SceneLoader
	{
	public:
		SceneLoader() = delete;
		~SceneLoader() = delete;

		static void Load(SceneManager* const sceneManager);

	private:
		static void loadScene(const WCHAR* fileName, std::vector<BoardObjectInfo>* const boardObjectInfos);
		static void loadScene(char* fileName, std::vector<BoardObjectInfo>* const boardObjectInfos);

	private:
		enum { RESERVE_SIZE = 64 };
	};
}

