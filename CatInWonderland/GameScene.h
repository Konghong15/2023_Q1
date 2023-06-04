#pragma once

#include <vector>

#include "Scene.h"
#include "BoardObject.h"
#include "eSpriteType.h"
#include "BoardObjectInfo.h"

namespace catInWonderland
{
	struct Sprite;
	class Player;
	class Brick;
	class Butterfly;
	class Button;
	class PlummetObject;
	class GuideButton;

	class GameScene : public Scene
	{
	public:
		GameScene(eSceneType sceneType, eSceneType nextScene, unsigned int boardSize, unsigned int limitRotateCount, float scale, eSpriteType stageTitleName, eSpriteType tileType, const std::vector<BoardObjectInfo>& boardObjectInfos);
		virtual ~GameScene() = default;

		virtual eSceneType HandleScene() override;
		virtual void Enter() override;
		virtual void Update() override;
		virtual void Render() override;
		virtual void Exit() override;

		inline void RegisterBoardObject(BoardObject* boardObject);

	protected:
		virtual void CreateBoardObject();
		virtual void CreateTileObject();
		virtual void CreateGuideButterfly(eAnimationType butterflyType, eSpriteType firstSpeechBubble, eSpriteType secondSpeechBubble);
		virtual void ExcuteButterfly(unsigned int index);
		virtual void TurnOffButterfly(unsigned int index);

	protected:
		enum { MAX_NUMBER_COUNT = 8 };
		static eSpriteType mNumbers[MAX_NUMBER_COUNT];

		std::vector<BoardObjectInfo> mBoardObjectInfos;
		const float mScale;
		std::vector <BoardObject*> mBoardObjects;
		Player* mPlayer;
		Brick* mBrick;
		Butterfly* mButterfly;
		Button* mReturnButton;
		unsigned int mBoardSize;
		eSceneType mNextScene;
		const float mEndClearInterval;
		float mClearInterval;

		bool mbRotateLeft;
		float mRotateSceneElapsed;
		bool mbRotateScene;
		float mRotateObjectElapsed;
		bool mbRotateObject;

		const unsigned int mLimitRotateCount;
		unsigned int mRotateCount;
		eSpriteType mStageTitleName;
		eSpriteType mTileType;

		PlummetObject* mClearImage;
		PlummetObject* mStageTitle;
		PlummetObject* mRotateImage;
		PlummetObject* mRotateCountImage;
		GuideButton* mGuideButterflyOrNull;
		GuideButton* mGuideSpeechOrNull[2];
		float mPlayerIdleElapsed;;
	};

	void GameScene::RegisterBoardObject(BoardObject* boardObject)
	{
		mBoardObjects.push_back(boardObject);
		RegisterObject(static_cast<Object*>(boardObject));
	}
}