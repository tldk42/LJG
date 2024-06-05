#pragma once
#include "CommonInclude.h"

namespace LJG
{
	class ObjectManager
	{
	private:
		ObjectManager();

	public:
		static void Initialize();
		static void Update(float DeltaTime);
		static void Render();
		static void Release();

		inline static void AddObject(class UObject* Object) { s_ObjectManager->AddObject_Internal(Object); }

	private:
		void AddObject_Internal(UObject* Object);

	private:
		std::vector<class UObject*> mObjects;

	private:
		static ObjectManager* s_ObjectManager;
	};
}
