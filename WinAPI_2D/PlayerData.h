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
	End
};
