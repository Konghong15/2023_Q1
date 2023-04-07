#include "Helper.h"
#include "Collider.h"
#include "ColliderManager.h"
#include "ObjectManager.h"

namespace hongpireSurvivors
{
	int Helper::Clamp(int min, int max, int num)
	{
		num = min > num ? min : num;
		num = max < num ? max : num;

		return num;
	}

	void Helper::Spawn(Object* object, SHORT x, SHORT y, SHORT sizeX, SHORT sizeY)
	{
		ObjectManager::GetInstance()->OnSpawn(object);
		Collider* col2 = new Collider({ sizeX, sizeY }, { 0, 0 }, *object);
		object->AddCollider(col2);
		ColliderManager::GetInstance()->OnRegister(col2);
	}
}