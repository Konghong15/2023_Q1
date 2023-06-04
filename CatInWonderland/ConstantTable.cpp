#include <cmath>

#include "ConstantTable.h"


namespace catInWonderland
{
	const float PLAYER_MOVE_TIME = 0.5f;
	const float PLAYER_PLUMMET_TIME = 0.3f;
	const float PLAYER_ACTION_TIME = 0.6f;
	const float STAGE_TITLE_PLUMMET_TIME = 0.5f;
	const float ROTATE_COUNT_PLUMMET_TIME = 0.5f;
	const float CLEAR_PLUMMET_TIME = 0.5f;

	const float PLAYER_IDLE_INTERVAL = 0.5f;
	const float PLAYER_MOVE_INTERVAL = 0.1f;
	const float PLAYER_PlUMMET_INTERVAL = 0.25f;
	const float PLAYER_ACTION_INTERVAL = 0.1f;
	const float STAGE_TITLE_PLUMMET_DISTANCE = 0.f;
	const float ROTATE_COUNT_PLUMMET_DISTANCE = 0.f;
	const float CLEAR_PLUMMET_DISTANCE = 500.f;
	const float BUTTERPLY_IDLE_INTERVAL = 0.2f;

	const hRectangle TITLE_TEXT_RECT(0, 0, 1281, 805);
	const hRectangle TILE_RECT(0, 0, 360, 360);
	const hRectangle BACKGROUND_RECT(0, 0, 1920, 1080);
	const hRectangle BUTTER_FLY_RECT(0, 0, 218, 206);
	const hRectangle BRICK_RECT(-30, -30, 423, 213);
	const hRectangle OBSTACLE_RECT(0, 0, 360, 360);
	const hRectangle TITLE_CHANGECOLORTILE_RECT(-50, -50, 410, 410);
	const hRectangle TITLE_TEXT_CHALLENGE_SPRITE_RECT(0, 0, 333, 326);
	const hRectangle PORTAL_RECT(-200, -90, 550, 550);
	const hRectangle CLEAR_SPRITE_RECT(0, 0, 848, 595);
	const hRectangle DIRECTION_SPRITE_RECT(0, 0, 256, 169);
	const hRectangle STAGE_TITLE_SPRITE_RECT(0, 0, 682, 139);
	const hRectangle ROTATE_COUNT_SPRITE_RECT(0, 0, 390, 860);
	const hRectangle NUMBER_SPRITE_RECT(0, 0, 142, 148);
	const hRectangle UI_SPRITE_RECT(0, 0, 175, 157);
	const hRectangle TITLE_BUTTON_RECT(0, 0, 384, 129);
	const hRectangle BUTTON_A_SPRITE_RECT(0, 0, 147, 214);
	const hRectangle BUTTON_D_SPRITE_RECT(0, 0, 147, 214);
	const hRectangle BUTTON_Q_SPRITE_RECT(0, 0, 147, 214);
	const hRectangle BUTTON_W_SPRITE_RECT(0, 0, 147, 214);
	const hRectangle BUTTON_E_SPRITE_RECT(0, 0, 147, 214);
	const hRectangle SET_BUTTON_RECT(0, 0, 175, 157);
	const hRectangle ROTATE_COUNT_NUMBER_SPRITE_RECT(-50, -50, 209, 190);
	const hRectangle SPACE_BUTTON_RECT(0, 0, 420, 148);
	const hRectangle GUIDE_BUTTERFLY(0, 0, 335, 346);

	const hRectangle TITLE_TEXT_WORLD_RECT(565, 76, 1412, 621);
	const hRectangle TITLE_TEXT_START_RECT(801, 736, 1176, 840);
	const hRectangle TITLE_TEXT_CHALLENGE_RECT(1633, 330, 1877, 569);
	const hRectangle TITLE_TEXT_EXIT_RECT(801, 877, 1176, 981);
	const hRectangle CLEAR_WORLD_RECT(536, -300, 1384, 300);
	const hRectangle STAGE_TITLE_WORLD_RECT(620, 22, 1301, 160);
	const hRectangle ROTATE_COUNT_WORLD_RECT(1422, 0, 1676, 589);
	const hRectangle BUTTON_A_WORLD_RECT(383, 691, 573, 909);
	const hRectangle BUTTON_D_WORLD_RECT(820, 691, 1009, 909);
	const hRectangle BUTTON_Q_WORLD_RECT(450, 77, 577, 215);
	const hRectangle SPACE_BUTTON_WORLD_RECT(1371, 894, 1579, 957);
	const hRectangle BUTTON_W_WORLD_RECT(1155, 363, 1300, 590);
	const hRectangle ROTATE_COUNT_NUMBER_WORLD_RECT(1422, 300, 1676, 550);
	const hRectangle BUTTON_E_WORLD_RECT(1330, 872, 1457, 1010);
	const hRectangle GUIDE_BUTTERFLY_RECT(21, 697, 354, 1000);
}