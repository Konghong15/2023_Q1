#include <Windows.h>
#include "Scene.h"

namespace hockman
{
	Scene::Scene(COORD sceneSize, COORD camaraPos)
		: mSceneSize(sceneSize)
		, mCamaraPos(camaraPos)
	{
	}
}