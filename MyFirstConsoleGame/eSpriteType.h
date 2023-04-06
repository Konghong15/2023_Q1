#pragma once

namespace hongpireSurvivors
{
	enum class eSpriteType
	{
		PLAYER_IDLE,
		PLAYER_RUN,
		PLAYER_ATTACK,
		PLAYER_JUMP,
		MONSTER_LEFT,
		PROJECTILE_LEFT,
		PROJECTILE_RIGHT,
		MAP_1,
		ENEMY_0, // 15 17
		ENEMY_1, // 20 13
		ENEMY_2, // 20 8
		BOSS_0_IDLE, // 30 29
		BOSS_0_JUMP, // 30 28
		BOSS_1_IDLE, // 30 26
		BOSS_1_ATTACK, // 30 23
		BOSS_2_IDLE, // 35 33
		BOSS_2_ATTACK, // 35 31
		BOSS_2_PROJECTILE, // 15 8
	};
}