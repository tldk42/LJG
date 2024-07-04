#include "DoPunch.h"

#include "InputManager.h"
#include "Game/Object/Game_2/Enemy/ACroaks.h"
#include "Game/Object/Game_2/Enemy/ARibby.h"
#include "Game/Object/Game_2/Enemy/FrogProjectile.h"
#include "Helper/EngineHelper.h"

namespace LJG::AI
{

	Fire_Punch::Fire_Punch()
		: Node("Test2!") {}

	ENodeState Fire_Punch::Evaluate()
	{
		/// FirePunch 작동 조건
		/// 1. Phase 1
		/// 2. Croaks State & Ribby State != Intro && Ribby State == Idle 
		/// 3. Ribby & Croaks Health > 0
		if (Croaks.GetState() == EnumAsByte(ECroaksState::Idle))
		{
			if (Croaks.GetCurrentHealth() > 0.f)
			{
				Ribby.SetState(EnumAsByte(ERibbyState::Attack_Punch_Start));
				Croaks.SetState(EnumAsByte(ECroaksState::Idle));
				return ENodeState::Success;
			}
		}

		return ENodeState::Failure;


		if (Manager_Input.IsKeyDown(EKeyCode::RButton))
		{
			LOG_CORE_INFO("Fire_Punch SUCCESS");
			FrogProjectile* projectile = Manager_Object.Spawn<FrogProjectile>(EGame2Projectile::Fist);
			projectile->SetOwnerActor(&Ribby);
			projectile->Launch();
			return ENodeState::Success;
		}
		if (Manager_Input.IsKeyDown(EKeyCode::LButton))
		{
			LOG_CORE_INFO("Fire_Punch FAIL");
			return ENodeState::Failure;
		}
		else
		{
			return ENodeState::Running;
		}
	}
}
