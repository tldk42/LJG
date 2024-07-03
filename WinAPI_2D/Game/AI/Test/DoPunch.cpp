#include "DoPunch.h"

#include "InputManager.h"
#include "Game/Object/Game_2/Enemy/FrogProjectile.h"

namespace LJG::AI
{

	DoPunch::DoPunch()
		: Node("Test2!") {}

	ENodeState DoPunch::Evaluate()
	{
		if (Manager_Input.IsKeyDown(EKeyCode::RButton))
		{
			LOG_CORE_INFO("DoPunch SUCCESS");
			FrogProjectile* projectile = Manager_Object.Spawn<FrogProjectile>(EGame2Projectile::Fist);
			projectile->SetOwnerActor(GetRoot()->Owner);
			projectile->Launch();
			return ENodeState::Success;
		}
		if (Manager_Input.IsKeyDown(EKeyCode::LButton))
		{
			LOG_CORE_INFO("DoPunch FAIL");
			return ENodeState::Failure;
		}

		return ENodeState::Running;

	}
}
