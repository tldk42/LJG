#include "SoundManager.h"
#include "Component/UAudio.h"
#include <fmod.hpp>
#include <fmod_errors.h>

namespace LJG
{
	void SoundManager::Initialize()
	{
		Get().Initialize_Internal();
	}

	void SoundManager::Update(float DeltaTime)
	{
		Get().mFmodSystem->update();
	}

	void SoundManager::Render() {}

	void SoundManager::Release()
	{
		for (auto& audio : Get().mManagedList)
		{
			audio.second.release();
		}

		Get().Release_Internal();
	}

	void SoundManager::Initialize_Internal()
	{
		FMOD_RESULT result;

		// Creates an instance of the FMOD system.
		result = System_Create(&mFmodSystem);

		assert(result == FMOD_OK, "fmod system creation failed");

		// Initialize the system object and prepare FMOD for playback.
		result = mFmodSystem->init(32, FMOD_INIT_NORMAL, nullptr);

		assert(result == FMOD_OK, "fmod system initialize failed");
	}

	void SoundManager::Release_Internal()
	{
		if (mFmodSystem)
		{
			mFmodSystem->close();
			mFmodSystem->release();
			mFmodSystem = nullptr;
		}
	}
}
