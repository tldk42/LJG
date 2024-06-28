#pragma once

enum class EPlayerAnimState : uint8_t
{
	Idle,
	Move,
	Move_Shoot,
	Shoot,
	Jump,
	Duck_Start,
	Duck_Idle,
	Duck_Shoot
};
