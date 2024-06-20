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
		static void Initialize();
		static void Update(float DeltaTime);
		static void Render();
		static void Release();

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
