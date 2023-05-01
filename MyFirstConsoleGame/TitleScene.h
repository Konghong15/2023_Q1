#pragma once

#include "Scene.h"

namespace hongpireSurvivors
{
	enum class eSelect
	{
		START,
		OPTION,
		EXIT
	};

	class TitleScene : public Scene
	{
	public:
		TitleScene(eSpriteType background, COORD sceneSize, COORD camaraPos = { 0,0 });
		~TitleScene() = default;

		virtual void Enter() override;
		virtual void Frame() override;
		virtual void Exit() override;
	
	private:
		eSpriteType mBGSpriteType;
		eSelect mSelect;
	};
}