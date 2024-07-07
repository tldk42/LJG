#pragma once

enum class EPlayerAnimState : uint8_t
{
	Idle,
	Move,
	Move_Shoot,
	Move_Shoot_Diagonal,
	Shoot,
	Shoot_Up,
	Jump,
	Parry,
	Duck_Start,
	Duck_Idle,
	Duck_Shoot,
	Dash_Ground,
	Dash_Air,
	ExecSkill_Straight,
	ExecSkill_Up,
	ExecSkill_Diagonal,
	Hit,
	End
};

enum class EPlayerMontages : uint8_t
{
	Exec_Straight,
	Exec_Up,
	Exec_Diagonal,
	Hit
};
