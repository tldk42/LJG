#include "Ribby_Phase2.h"

#include "InputManager.h"
#include "Game/Object/Game_2/Enemy/ACroaks.h"
#include "Game/Object/Game_2/Enemy/ARibby.h"

namespace LJG::AI
{
	Ribby_Phase2::Ribby_Phase2() {}

	ENodeState Ribby_Phase2::Evaluate()
	{
		switch (static_cast<ERibbyState>(Ribby.GetState()))
		{
		case ERibbyState::Idle:
			// Check ���� ����
			Ribby.CheckSpikeCoolTime();
			return ENodeState::Running;
		case ERibbyState::Attack_Spike_Intro_Start:
			// �ڵ� Transition ->Spike Intro Loop
			return ENodeState::Running;
		case ERibbyState::Attack_Spike_Intro_Loop:
			// Check �� ������ ����
			Ribby.TryAttack_Spike();
			return ENodeState::Running;
		case ERibbyState::Attack_Spike_Loop:
			// �ִ� ���̼� Notify���� �� ����	
			return ENodeState::Running;
		}

		return ENodeState::Failure;
	}
}
