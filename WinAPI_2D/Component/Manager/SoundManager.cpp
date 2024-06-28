#include "SoundManager.h"
#include "Component/UAudio.h"
#include <fmod.hpp>
#include <fmod_errors.h>

namespace LJG
{
	void SoundManager::Initialize()
	{
		FMOD_RESULT result;

		// Creates an instance of the FMOD system.
		result = System_Create(&mFmodSystem);

		assert(result == FMOD_OK, "fmod system creation failed");

		// Initialize the system object and prepare FMOD for playback.
		result = mFmodSystem->init(32, FMOD_INIT_NORMAL, nullptr);

		assert(result == FMOD_OK, "fmod system initialize failed");
	}

	void SoundManager::Update(float DeltaTime)
	{
		mFmodSystem->update();
	}

	void SoundManager::Render() {}

	void SoundManager::Release()
	{
		if (mFmodSystem)
		{
			mFmodSystem->close();
			mFmodSystem->release();
			mFmodSystem = nullptr;
		}
	}

	void SoundManager::Stop() {}

	void SoundManager::StopAll()
	{
		for (auto& list : mManagedList)
		{
			list.second->Stop();
		}
	}

	void SoundManager::Pause() {}

	void SoundManager::PauseAll()
	{
		for (auto& list : mManagedList)
		{
			list.second->Pause();
		}
	}

}
