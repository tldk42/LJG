#include "ObjectManager.h"

#include "UObject.h"
#include "Window.h"

namespace LJG
{
	void ObjectManager::Initialize()
	{
		Window::GetWindow()->OnResize.emplace_back([this](UINT InWidth, UINT InHeight){
			OnResizeCallback(InWidth, InHeight);
		});
	}

	void ObjectManager::Update(float DeltaTime)
	{
		RemoveInvalidObjects();

		for (const auto& obj : mManagedObjects)
		{
			obj.second->Update(DeltaTime);
		}
	}

	void ObjectManager::Render()
	{
		for (const auto& obj : mManagedObjects)
		{
			obj.second->Render();
		}
	}

	void ObjectManager::Release()
	{}


	void ObjectManager::RemoveInvalidObjects()
	{
		for (auto it = mManagedObjects.begin(); it != mManagedObjects.end();)
		{
			if (!it->second)
			{
				it = mManagedObjects.erase(it);
			}
			else
			{
				++it;
			}
		}
	}

	void ObjectManager::OnResizeCallback(UINT InWidth, UINT InHeight)
	{
		for (const auto& obj : mManagedObjects)
		{
			// obj_ptr->OnResize();
		}
	}
}
