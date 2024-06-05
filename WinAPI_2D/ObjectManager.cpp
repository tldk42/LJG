#include "ObjectManager.h"

#include "UObject.h"

namespace LJG
{
	ObjectManager* ObjectManager::s_ObjectManager;

	ObjectManager::ObjectManager()
	{
		mObjects.reserve(10);
	}

	void ObjectManager::Initialize()
	{
		if (s_ObjectManager)
			return;

		s_ObjectManager = new ObjectManager;
	}

	void ObjectManager::Update(float DeltaTime)
	{
		if (s_ObjectManager)
		{
			for (UObject*& obj : s_ObjectManager->mObjects)
			{
				obj->Update(DeltaTime);
			}
		}
	}

	void ObjectManager::Render()
	{
		if (s_ObjectManager)
		{
			for (UObject*& obj : s_ObjectManager->mObjects)
			{
				obj->Render();
			}
		}
	}

	void ObjectManager::Release()
	{
		if (s_ObjectManager)
		{
			for (UObject*& obj : s_ObjectManager->mObjects)
			{
				obj->Release();
			}
		}
	}

	void ObjectManager::AddObject_Internal(UObject* Object)
	{
		mObjects.emplace_back(Object);
	}
}
