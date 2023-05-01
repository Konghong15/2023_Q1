#include <Windows.h>
#include "Scene.h"

namespace hongpireSurvivors
{
	Scene::Scene(COORD sceneSize, COORD camaraPos)
		: mSceneSize(sceneSize)
		, mCamaraPos(camaraPos)
	{
	}
}