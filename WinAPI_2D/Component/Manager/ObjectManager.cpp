#include "ObjectManager.h"
#include <ranges>
#include "Component/UObject.h"

namespace LJG
{
	void ObjectManager::Initialize()
	{}

	void ObjectManager::Update(float DeltaTime)
	{
		std::vector<UObject*> defferedDeSpawnObj;
		for (const auto& object : mManagedList | std::views::values)
		{
			if (object)
			{
				if (object->bActive)
				{
					object->Update(DeltaTime);
				}
				else if (object->bIsPoolManaged)
				{
					defferedDeSpawnObj.emplace_back(object.get());
				}
			}
		}
		for (UObject* obj : defferedDeSpawnObj)
		{
			DeSpawn(obj);
		}
	}

	void ObjectManager::Render()
	{
		for (const auto& object : mManagedList | std::views::values)
		{
			if (object->bActive)
			{
				object->Render();
			}
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

	bool ObjectManager::DestroyObject(const WText& InObjName)
	{
		TrySafeRemove(InObjName);

		return true;
	}

}
