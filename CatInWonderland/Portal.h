#pragma once
#include "BoardObject.h"

namespace catInWonderland
{
	class Portal : public BoardObject
	{
	public:
		Portal(const ObjectInfo& objectInfo, size_t boardX, size_t boardY, bool bPortalColor);
		Portal(hRectangle worldRectangle, hRectangle spriteRectangle, eSpriteType spriteType, eLayerType layerType, size_t boardX, size_t boardY, bool bPortalColor, bool bLeft = true);
		virtual ~Portal() = default;

		virtual void Update(float deltaTime);

		inline void SetConnectedPortal(Portal* connectedPortal);
		inline bool PortalColor() const;
		inline const Portal& GetConnectedPortal() const;

	private:
		Portal* mConnectedPortal;
		bool mbPortalColor;
	};

	bool Portal::PortalColor() const
	{
		return mbPortalColor;
	}

	const Portal& Portal::GetConnectedPortal() const
	{
		return *mConnectedPortal;
	}

	void Portal::SetConnectedPortal(Portal* connectedPortal)
	{
		mConnectedPortal = connectedPortal;
	}
}