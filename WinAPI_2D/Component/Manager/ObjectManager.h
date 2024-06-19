#pragma once
#include "Manager.h"

namespace LJG
{
	#define Manager_Object ObjectManager::Get()

	class ObjectManager : public ManagerBase<UObject, ObjectManager>
	{
	public:
		static void Initialize();
		static void Update(float DeltaTime);
		static void Render();

	private:
		// Resize Callback
		void OnResizeCallback(UINT InWidth, UINT InHeight);

	private:
		friend class TSingleton<ObjectManager>;
		ObjectManager()  = default;
		~ObjectManager() = default;

	public:
		ObjectManager(const ObjectManager&)            = delete;
		ObjectManager& operator=(const ObjectManager&) = delete;

	};

}
