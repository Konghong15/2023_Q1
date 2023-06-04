#include <cassert>
#include <fstream>

#include "SceneLoader.h"
#include "SceneManager.h"
#include "SceneStart.h"
#include "Stage01.h"
#include "Stage02.h"
#include "Stage03.h"
#include "Stage04.h"
#include "Stage05.h"
#include "Stage06.h"
#include "Stage07.h"
#include "Stage08.h"
#include "Stage09.h"
#include "Stage10.h"
#include "eObjectType.h"
#include "CutScene.h"
#include "CutScene01.h"
#include "CutScene02.h"
#include "CutScene03.h"

namespace catInWonderland
{
	void SceneLoader::Load(SceneManager* const sceneManager)
	{
		assert(sceneManager != nullptr);

		sceneManager->RegisterScene(eSceneType::START, new SceneStart());

		std::vector<BoardObjectInfo> boardObjectInfos;
		boardObjectInfos.reserve(RESERVE_SIZE);
		loadScene(L".\\resources\\coordinate\\stage01.txt", &boardObjectInfos);
		sceneManager->RegisterScene(eSceneType::STAGE01, new Stage01(boardObjectInfos));
		loadScene(L".\\resources\\coordinate\\stage02.txt", &boardObjectInfos);
		sceneManager->RegisterScene(eSceneType::STAGE02, new Stage02(boardObjectInfos));
		loadScene(L".\\resources\\coordinate\\stage03.txt", &boardObjectInfos);
		sceneManager->RegisterScene(eSceneType::STAGE03, new Stage03(boardObjectInfos));
		loadScene(L".\\resources\\coordinate\\stage04.txt", &boardObjectInfos);
		sceneManager->RegisterScene(eSceneType::STAGE04, new Stage04(boardObjectInfos));
		loadScene(L".\\resources\\coordinate\\stage05.txt", &boardObjectInfos);
		sceneManager->RegisterScene(eSceneType::STAGE05, new Stage05(boardObjectInfos));
		loadScene(L".\\resources\\coordinate\\stage06.txt", &boardObjectInfos);
		sceneManager->RegisterScene(eSceneType::STAGE06, new Stage06(boardObjectInfos));
		loadScene(L".\\resources\\coordinate\\stage07.txt", &boardObjectInfos);
		sceneManager->RegisterScene(eSceneType::STAGE07, new Stage07(boardObjectInfos));
		loadScene(L".\\resources\\coordinate\\stage08.txt", &boardObjectInfos);
		sceneManager->RegisterScene(eSceneType::STAGE08, new Stage08(boardObjectInfos));
		loadScene(L".\\resources\\coordinate\\stage09.txt", &boardObjectInfos);
		sceneManager->RegisterScene(eSceneType::STAGE09, new Stage09(boardObjectInfos));
		loadScene(L".\\resources\\coordinate\\stage10.txt", &boardObjectInfos);
		sceneManager->RegisterScene(eSceneType::STAGE10, new Stage10(boardObjectInfos));

		sceneManager->RegisterScene(eSceneType::CutScene01, new CutScene01());
		sceneManager->RegisterScene(eSceneType::CutScene02, new CutScene02());
		sceneManager->RegisterScene(eSceneType::CutScene03, new CutScene03());

	}

	void SceneLoader::loadScene(const WCHAR* fileName, std::vector<BoardObjectInfo>* const boardObjectInfos)
	{
		std::ifstream fin;
		fin.open(fileName, std::ios_base::in);

		assert(fin.is_open());

		unsigned int id;
		BoardObjectInfo boadrObjectInfo;
		std::string trash;
		boardObjectInfos->clear();

		while (true)
		{
			fin >> boadrObjectInfo.BoardX;
			fin >> boadrObjectInfo.BoardY;
			fin >> id;

			boadrObjectInfo.ObjectType = static_cast<eObjectType>(id);

			if (!fin.fail())
			{
				boardObjectInfos->push_back(boadrObjectInfo);
				continue;
			}

			if (fin.eof())
			{
				break;
			}

			fin.clear();
			fin >> trash;
		}

		fin.close();
	}

	void SceneLoader::loadScene(char* fileName, std::vector<BoardObjectInfo>* const boardObjectInfos)
	{
		std::ifstream fin;
		fin.open(fileName, std::ios_base::in);

		assert(fin.is_open());

		unsigned int id;
		BoardObjectInfo boadrObjectInfo;
		std::string trash;
		boardObjectInfos->clear();

		while (true)
		{
			fin >> boadrObjectInfo.BoardX;
			fin >> boadrObjectInfo.BoardY;
			fin >> id;

			boadrObjectInfo.ObjectType = static_cast<eObjectType>(id);

			if (!fin.fail())
			{
				boardObjectInfos->push_back(boadrObjectInfo);
				continue;
			}

			if (fin.eof())
			{
				break;
			}

			fin.clear();
			fin >> trash;
		}

		fin.close();
	}
}