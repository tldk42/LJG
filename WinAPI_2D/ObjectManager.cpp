#include "ObjectManager.h"

#include "UObject.h"
#include "Window.h"

namespace LJG
{
	ObjectManagerUPtr ObjectManager::s_ObjectManager;

	ObjectManager::ObjectManager()
	{
		mObjects.reserve(10);

		Window::GetWindow()->OnResize.emplace_back([this](UINT InWidth, UINT InHeight){
			OnResizeCallback(InWidth, InHeight);
		});
	}

	ObjectManager::~ObjectManager()
	{
		ObjectManager::Release();
	}

	void ObjectManager::Initialize()
	{
		if (s_ObjectManager)
			return;

		s_ObjectManager.reset(new ObjectManager());
	}

	void ObjectManager::Update(float DeltaTime)
	{
		if (s_ObjectManager)
		{
			for (UObjectSPtr& obj : s_ObjectManager->mObjects)
			{
				obj->Update(DeltaTime);
			}
		}
	}

	void ObjectManager::Render()
	{
		if (s_ObjectManager)
		{
			for (UObjectSPtr& obj : s_ObjectManager->mObjects)
			{
				obj->Render();
			}
		}
	}

	void ObjectManager::Release()
	{
		s_ObjectManager->mObjects.clear();
	}

	void ObjectManager::AddObject_Internal(UObject* InObject)
	{
		mObjects.emplace_back(InObject);
	}

	void ObjectManager::OnResizeCallback(UINT InWidth, UINT InHeight)
	{
		for (const UObjectSPtr& obj_ptr : mObjects)
		{
			// obj_ptr->OnResize();
		}
	}
}
