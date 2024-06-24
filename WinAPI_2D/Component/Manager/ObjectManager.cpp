#include "ObjectManager.h"

#include "AActor.h"
#include "Component/UObject.h"
#include "Window.h"

namespace LJG
{
	void ObjectManager::Initialize()
	{
		Window::GetWindow()->OnResize.Bind([](UINT InWidth, UINT InHeight){
			Get().OnResizeCallback(InWidth, InHeight);
		});
	}

	void ObjectManager::Update(float DeltaTime)
	{
		Get().RemoveInvalidResource();

		for (const auto& [key, object] : Get().mManagedList)
		{
			if (dynamic_cast<AActor*>(object.get()))
			{
				object->Update(DeltaTime);
			}
		}
	}

	void ObjectManager::Render()
	{
		for (const auto& [key, object] : Get().mManagedList)
		{
			if (dynamic_cast<AActor*>(object.get()))
			{
				object->Render();
			}
		}
	}


	void ObjectManager::OnResizeCallback(UINT InWidth, UINT InHeight)
	{
		for (const auto& obj : mManagedList)
		{
			// obj_ptr->OnResize();
		}
	}
}
