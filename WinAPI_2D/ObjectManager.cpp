#include "ObjectManager.h"

#include "Component/UObject.h"
#include "Window.h"

namespace LJG
{
	void ObjectManager::Initialize()
	{
		Window::GetWindow()->OnResize.emplace_back([](UINT InWidth, UINT InHeight){
			Get().OnResizeCallback(InWidth, InHeight);
		});
	}

	void ObjectManager::Update(float DeltaTime)
	{
		Get().RemoveInvalidObjects();

		for (const auto& [key, object] : Get().mManagedObjects)
		{
			if (!object->GetParent())
			{
				object->Update(DeltaTime);
			}
		}
	}

	void ObjectManager::Render()
	{
		for (const auto& [key, object] : Get().mManagedObjects)
		{
			if (!object->GetParent())
			{
				object->Render();
			}
		}
	}


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
