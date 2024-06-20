#pragma once
#include "Manager.h"

namespace LJG
{
	class UAudio;

	class SoundManager : ManagerBase<UAudio, SoundManager>
	{
	private:
		friend class TSingleton<SoundManager>;
		SoundManager()  = default;
		~SoundManager() = default;

	public:
		SoundManager(const SoundManager&)            = delete;
		SoundManager& operator=(const SoundManager&) = delete;
	};
}
