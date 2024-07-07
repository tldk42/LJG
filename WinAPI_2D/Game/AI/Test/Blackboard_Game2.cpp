#include "Blackboard_Game2.h"

#include "Game/Object/Game_2/Enemy/ACroaks.h"
#include "Game/Object/Game_2/Enemy/ARibby.h"
#include "Helper/EngineHelper.h"

void LJG::Blackboard_Game2::ChangePhase() const
{
	switch (CurrentPhase)
	{
	case EGame2Phase::Phase1:
		Ribby.SetState(EnumAsByte(ERibbyState::Roll_Intro_Start));
		Croaks.SetState(EnumAsByte(ECroaksState::Idle));
		break;
	case EGame2Phase::Phase2:
		Ribby.SetState(EnumAsByte(ERibbyState::Roll_Intro_Start));
		Croaks.SetState(EnumAsByte(ECroaksState::Morph_Intro));
		break;
	case EGame2Phase::Phase3:
		break;
	case EGame2Phase::End:
		break;
	}

	BB_Game2.CurrentHP    = Game2MonsterHP[EnumAsByte(BB_Game2.CurrentPhase)];
	BB_Game2.CurrentPhase = static_cast<EGame2Phase>(static_cast<uint8_t>(BB_Game2.CurrentPhase) + 1);

}
