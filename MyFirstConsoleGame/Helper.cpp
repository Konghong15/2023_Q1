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

	bool Helper::IsContain(COORD pos, COORD size, COORD point)
	{
		const COORD END = { pos.X + size.X , pos.Y + size.Y };

		return pos.X <= point.X && pos.Y <= point.Y && END.X >= point.X && END.Y >= point.Y;
	}	
	
	bool Helper::IsContain(COORD pos, COORD size, POINT point)
	{
		const COORD END = { pos.X + size.X , pos.Y + size.Y };

		return pos.X <= point.x && pos.Y <= point.y && END.X >= point.x && END.Y >= point.y;
	}

	void Helper::Spawn(Object* object, SHORT sizeX, SHORT sizeY)
	{
		ObjectManager::GetInstance()->OnSpawn(object);
		Collider* collider = new Collider({ sizeX, sizeY }, { 0, 0 }, *object);
		object->AddCollider(collider);
		ColliderManager::GetInstance()->OnRegister(collider);
	}
}