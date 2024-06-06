#pragma once
#include "CommonInclude.h"

namespace LJG
{
	CLASS_PTR(ObjectManager)

	class ObjectManager
	{
	private:
		ObjectManager();

	public:
		~ObjectManager();

	public:
		static void Initialize();
		static void Update(float DeltaTime);
		static void Render();
		static void Release();

		inline static void AddObject(class UObject* Object) { s_ObjectManager->AddObject_Internal(Object); }

	private:
		void AddObject_Internal(UObject* Object);

	private:
		std::vector<UObjectSPtr> mObjects;

	private:
		static ObjectManagerUPtr s_ObjectManager;
	};
}
