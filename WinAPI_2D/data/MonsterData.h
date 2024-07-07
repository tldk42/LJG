#pragma once
#include <cstdint>

enum class EGame2Projectile : uint8_t
{
	Fist,
	Butterfly,
	Spike,
	Coin,
	Wheel
};

enum EFistType : uint8_t
{
	Normal = 0,
	Pink = 1
};

enum EBallType : uint8_t
{
	Blue = 0,
	Yellow = 1,
	Green = 2
};

enum class EGame2Phase : uint8_t
{
	Phase1,
	Phase2,
	Phase3,
	End
};

enum class ERibbyState : uint8_t
{
	Intro = 0,
	Idle,
	Roll_Intro_Start,
	Roll_Intro_Loop,
	Roll_Intro_End,
	Roll_Loop,
	Roll_End,
	Attack_Punch_Start,
	Attack_Punch_Loop,
	Attack_Punch_End,
	Attack_Spike_Intro_Start,
	Attack_Spike_Intro_Loop,
	Attack_Spike_Loop,
	Dead,
	End
};

enum class ECroaksState : uint8_t
{
	Intro = 0,
	Idle,
	Roll_Left,
	Roll_Right,
	Attack_Spit_Start,
	Attack_Spit_Loop,
	Attack_Spit_End,
	Attack_Fan_Start,
	Attack_Fan_Loop1,
	Attack_Fan_Loop2,
	Attack_Fan_End,
	Morph_Intro,
	Morph_Loop,
	Morph_Outro,
	Dead,
	End
};

enum class EFireflyState : uint8_t
{
	Idle,
	Down,
	Up,
	Left,
	Dead,
	End
};

enum class ESlotMachineState : uint8_t
{
	Intro = 0,
	Idle,
	Arm_Move_Start,
	Arm_Move_Idle, // 패링 가능
	Slot_Open,
	Attack_Coin,
	Attack_Cow,
	Attack_Snake,
	Attack_Tiger,
	Dead,
	End
};

constexpr float Game2MonsterHP[3] = {408, 714, 578};
