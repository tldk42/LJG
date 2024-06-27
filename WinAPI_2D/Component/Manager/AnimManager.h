#pragma once
#include "Manager.h"


namespace LJG
{
	struct FAnimData;

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
