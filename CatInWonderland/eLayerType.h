#pragma once

namespace catInWonderland
{
	enum class eLayerType
	{
		Background,		// ui, 배경화면
		BlendObject,	// tile과 투명처리될 오브젝트
		NonBlendObject,	// tile이 아닌 모든 오브젝트
		PostProcessing,	// 후처리 기능
		Size
	};
}