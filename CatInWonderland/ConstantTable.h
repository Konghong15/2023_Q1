#pragma once

#include "hRectangle.h"

namespace catInWonderland
{
	// movement duration time
	extern const float PLAYER_MOVE_TIME;
	extern const float PLAYER_PLUMMET_TIME;
	extern const float PLAYER_ACTION_TIME;
	extern const float STAGE_TITLE_PLUMMET_TIME;
	extern const float ROTATE_COUNT_PLUMMET_TIME;
	extern const float CLEAR_PLUMMET_TIME;

	// distance
	extern const float STAGE_TITLE_PLUMMET_DISTANCE;
	extern const float ROTATE_COUNT_PLUMMET_DISTANCE;
	extern const float CLEAR_PLUMMET_DISTANCE;

	// animation interval
	extern const float PLAYER_IDLE_INTERVAL;
	extern const float PLAYER_MOVE_INTERVAL;
	extern const float PLAYER_PlUMMET_INTERVAL;
	extern const float PLAYER_ACTION_INTERVAL;
	extern const float BUTTERPLY_IDLE_INTERVAL;
	
	// sprite rect
	extern const hRectangle TITLE_TEXT_RECT;
	extern const hRectangle TILE_RECT;
	extern const hRectangle BACKGROUND_RECT;
	extern const hRectangle BUTTER_FLY_RECT;
	extern const hRectangle BRICK_RECT;
	extern const hRectangle OBSTACLE_RECT;
	extern const hRectangle TITLE_CHANGECOLORTILE_RECT;
	extern const hRectangle TITLE_TEXT_CHALLENGE_SPRITE_RECT;
	extern const hRectangle PORTAL_RECT;
	extern const hRectangle CLEAR_SPRITE_RECT;
	extern const hRectangle DIRECTION_SPRITE_RECT;
	extern const hRectangle STAGE_TITLE_SPRITE_RECT;
	extern const hRectangle ROTATE_COUNT_SPRITE_RECT;
	extern const hRectangle NUMBER_SPRITE_RECT;
	extern const hRectangle UI_SPRITE_RECT;
	extern const hRectangle TITLE_BUTTON_RECT;
	extern const hRectangle BUTTON_A_SPRITE_RECT;
	extern const hRectangle BUTTON_D_SPRITE_RECT;
	extern const hRectangle BUTTON_W_SPRITE_RECT;
	extern const hRectangle SPACE_BUTTON_RECT;
	extern const hRectangle ROTATE_COUNT_NUMBER_SPRITE_RECT;
	extern const hRectangle SET_BUTTON_RECT;
	extern const hRectangle BUTTON_Q_SPRITE_RECT;
	extern const hRectangle BUTTON_E_SPRITE_RECT;
	extern const hRectangle GUIDE_BUTTERFLY;

	// world rect
	extern const hRectangle TITLE_TEXT_WORLD_RECT;
	extern const hRectangle TITLE_TEXT_START_RECT;
	extern const hRectangle TITLE_TEXT_CHALLENGE_RECT;
	extern const hRectangle TITLE_TEXT_EXIT_RECT;
	extern const hRectangle CLEAR_WORLD_RECT;
	extern const hRectangle STAGE_TITLE_WORLD_RECT;
	extern const hRectangle ROTATE_COUNT_WORLD_RECT;
	extern const hRectangle NUMBER_SPRITE_WORLD_RECT;
	extern const hRectangle DIRECTION_SPRITE_WORLD_RECT;
	extern const hRectangle BUTTON_A_WORLD_RECT;
	extern const hRectangle BUTTON_D_WORLD_RECT;
	extern const hRectangle BUTTON_W_WORLD_RECT;
	extern const hRectangle SPACE_BUTTON_WORLD_RECT;
	extern const hRectangle ROTATE_COUNT_NUMBER_WORLD_RECT;
	extern const hRectangle BUTTON_Q_WORLD_RECT;
	extern const hRectangle BUTTON_E_WORLD_RECT;
	extern const hRectangle GUIDE_BUTTERFLY_RECT;

	// cosf sinf
	extern const float COS_F[90];
	extern const float SIN_F[90];
}

// hRectangle worldRectangle, hRectangle spriteRectangle, Sprite* sprite, eLayerType layerType, float duration, float plummetDistance);