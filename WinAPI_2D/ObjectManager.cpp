#include "ObjectManager.h"

#include "UObject.h"

namespace LJG
{
	ObjectManagerUPtr ObjectManager::s_ObjectManager;

	ObjectManager::ObjectManager()
	{
		mObjects.reserve(10);
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
		// if (s_ObjectManager)
		// {
		// 	for (UObjectSPtr& obj : s_ObjectManager->mObjects)
		// 	{
		// 		obj->Release();
		// 		obj = nullptr;
		// 	}
		// }

		s_ObjectManager->mObjects.clear();
	}

	void ObjectManager::AddObject_Internal(UObject* Object)
	{
		mObjects.emplace_back(Object);
	}
}
