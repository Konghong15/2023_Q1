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

	void Helper::Spawn(Object* object, SHORT sizeX, SHORT sizeY)
	{
		ObjectManager::GetInstance()->OnSpawn(object);
		Collider* collider = new Collider({ sizeX, sizeY }, { 0, 0 }, *object);
		object->AddCollider(collider);
		ColliderManager::GetInstance()->OnRegister(collider);
	}
}