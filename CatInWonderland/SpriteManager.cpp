#include <fstream>
#include <string>

#include "RenderManager.h"
#include "SpriteManager.h"
#include "Sprite.h"

namespace catInWonderland
{
	SpriteManager::~SpriteManager()
	{
		for (auto iter = mSpriteMap.begin(); iter != mSpriteMap.end(); ++iter)
		{
			delete iter->second;
		}

		mSpriteMap.clear();
		mSpriteRectMap.clear();
	}

	void SpriteManager::LoadSpriteImage(eSpriteType spriteType, const WCHAR* fileName)
	{
		Sprite* sprite = new Sprite;
		sprite->Hdc = CreateCompatibleDC(RenderManager::GetInstance()->GetFrontDC());
		sprite->Bitmap = (HBITMAP)LoadImageW(nullptr, fileName, IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_LOADFROMFILE);
		assert(sprite->Bitmap != nullptr);
		HBITMAP prevBitmap = (HBITMAP)SelectObject(sprite->Hdc, sprite->Bitmap);
		DeleteObject(prevBitmap);

		GetObject(sprite->Bitmap, sizeof(BITMAP), &sprite->BitInfo);

		mSpriteMap.emplace(spriteType, sprite);
	}

	void SpriteManager::LoadSpriteImage(eSpriteType spriteType, const char* fileName)
	{
		Sprite* sprite = new Sprite;
		sprite->Hdc = CreateCompatibleDC(RenderManager::GetInstance()->GetFrontDC());
		sprite->Bitmap = (HBITMAP)LoadImageA(nullptr, fileName, IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_LOADFROMFILE);
		assert(sprite->Bitmap != nullptr);
		HBITMAP prevBitmap = (HBITMAP)SelectObject(sprite->Hdc, sprite->Bitmap);
		DeleteObject(prevBitmap);

		GetObject(sprite->Bitmap, sizeof(BITMAP), &sprite->BitInfo);

		mSpriteMap.emplace(spriteType, sprite);
	}

	void SpriteManager::LoadAnimationRectangle(eAnimationType animationType, const WCHAR* fileName, float interval)
	{
		std::ifstream fin;
		fin.open(fileName, std::ios_base::in);

		assert(fin.is_open());

		float x1;
		float y1;
		float x2;
		float y2;

		std::vector<hRectangle> spriteRectangles;
		spriteRectangles.reserve(32);
		std::string trash;

		while (true)
		{
			fin >> x1;
			fin >> y1;
			fin >> x2;
			fin >> y2;

			if (!fin.fail())
			{
				spriteRectangles.push_back(hRectangle(x1, y1, x2, y2));
				continue;
			}

			if (fin.eof())
			{
				break;
			}

			fin.clear();
			fin >> trash;
		}

		mSpriteRectMap.emplace(animationType, Animator(interval, spriteRectangles, true));
	}

	void SpriteManager::LoadAnimationRectangle(eAnimationType animationType, const char* fileName, float interval)
	{
		std::ifstream fin;
		fin.open(fileName, std::ios_base::in);

		assert(fin.is_open());

		float x1;
		float y1;
		float x2;
		float y2;

		std::vector<hRectangle> spriteRectangles;
		spriteRectangles.reserve(32);
		std::string trash;

		while (true)
		{
			fin >> x1;
			fin >> y1;
			fin >> x2;
			fin >> y2;

			if (!fin.fail())
			{
				spriteRectangles.push_back(hRectangle(x1, y1, x2, y2));
				continue;
			}

			if (fin.eof())
			{
				break;
			}

			fin.clear();
			fin >> trash;
		}

		mSpriteRectMap.emplace(animationType, Animator(interval, spriteRectangles, true));
	}
}