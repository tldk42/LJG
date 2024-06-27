#include "ObjectManager.h"

#include "Component/Actor/AActor.h"
#include "Component/UObject.h"
#include "Window.h"

namespace LJG
{
	void ObjectManager::Initialize()
	{}

	void ObjectManager::Update(float DeltaTime)
	{
		Get().RemoveInvalidResource();

		for (const auto& [key, object] : mManagedList)
		{
			object->Update(DeltaTime);
		}
	}

	void ObjectManager::Render()
	{
		for (const auto& [key, object] : mManagedList)
		{
			object->Render();
		}
	}

	void ObjectManager::Release()
	{
		for (auto it = mManagedList.cbegin(), next_it = it; it != mManagedList.cend(); it = next_it)
		{
			++next_it;
			if (!it->second->bDontDestroyOnLoad)
			{
				mManagedList.erase(it);
			}
		}
	}

}
