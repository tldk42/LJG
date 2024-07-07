#include "PeaShoot_Ex.h"

#include "Component/Animation/USpriteAnimation.h"
#include "Component/Manager/AnimManager.h"

namespace LJG
{

	PeaShoot_Ex::PeaShoot_Ex()
	{
		mAnim->SetAnimData(*Manager_Anim.GetResource(L"PeaShoot_Ex"));
	}

	PeaShoot_Ex::~PeaShoot_Ex() {}
}
