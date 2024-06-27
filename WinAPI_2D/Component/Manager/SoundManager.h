#pragma once
#include "Manager.h"

namespace FMOD
{
	class System;
}

namespace LJG
{
	#define Manager_Audio SoundManager::Get()

	class UAudio;

	class SoundManager : public ManagerBase<UAudio, SoundManager>
	{
	public:
		void Initialize();
		void Update(float DeltaTime);
		void Render();
		void Release();

	private:
		void Initialize_Internal();
		void Release_Internal();

	private:
		FMOD::System* mFmodSystem;

	private:
		friend class TSingleton<SoundManager>;
		friend class UAudio;
		SoundManager()  = default;
		~SoundManager() = default;

	public:
		SoundManager(const SoundManager&)            = delete;
		SoundManager& operator=(const SoundManager&) = delete;
	};
}
