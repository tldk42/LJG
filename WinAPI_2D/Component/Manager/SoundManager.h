#pragma once
#include "Manager.h"
#include "Component/UAudio.h"

namespace FMOD
{
	class System;
}

namespace LJG
{
	#define Manager_Audio SoundManager::Get()

	class SoundManager : public ManagerBase<UAudio, SoundManager>
	{
	public:
		void Initialize();
		void Update(float DeltaTime);
		void Render();
		void Release();

	public:
		void Stop();
		void StopAll();
		void Pause();
		void PauseAll();

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
