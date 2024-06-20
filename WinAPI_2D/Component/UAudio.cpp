#include "UAudio.h"

namespace LJG
{
	UAudio::UAudio(const WText& InKey)
	{
	}

	UAudio::~UAudio()
	{
	}

	void UAudio::Initialize()
	{
		FMOD_RESULT result;

		// Creates an instance of the FMOD system.
		result = System_Create(&mFmodSystem);

		assert(result == FMOD_OK, "fmod system creation failed");

		// Initialize the system object and prepare FMOD for playback.
		result = mFmodSystem->init(32, FMOD_INIT_NORMAL, nullptr);

		assert(result == FMOD_OK, "fmod system initialize failed");
	}

	void UAudio::Update(float DeltaTime)
	{
	}

	void UAudio::Render()
	{
	}

	void UAudio::Release()
	{
			if (mFmodSystem)
			{
				// Close the connection to the output and return to an uninitialized state without releasing the object.
				mFmodSystem->close();
				// Closes and frees this object and its resources.
				mFmodSystem->release();
			}
	}

	void UAudio::Load()
	{
	}
}
