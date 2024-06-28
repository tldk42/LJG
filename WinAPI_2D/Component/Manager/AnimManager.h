#pragma once
#include "Manager.h"
#include "Component/Animation/USpriteAnimation.h"


namespace LJG
{
	#define Manager_Anim AnimManager::Get()

	class AnimManager : public ManagerBase<FAnimData, AnimManager>
	{
	public:
		void LoadAllAnims();

	private:
		friend class TSingleton<AnimManager>;
		AnimManager()  = default;
		~AnimManager() = default;

	public:
		AnimManager(const AnimManager&)            = delete;
		AnimManager& operator=(const AnimManager&) = delete;
	};
}
