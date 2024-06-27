#pragma once
#include "Manager.h"
#include "Component/UObject.h"

namespace LJG
{
	#define Manager_Object ObjectManager::Get()

	class ObjectManager : public ManagerBase<UObject, ObjectManager>, public ICoreAPI
	{
	public:
#pragma region Core Interface
		void Initialize() override;
		void Update(float DeltaTime) override;
		void Render() override;
		void Release() override;
#pragma endregion

	private:
		friend class TSingleton<ObjectManager>;
		ObjectManager()  = default;
		~ObjectManager() = default;

	public:
		ObjectManager(const ObjectManager&)            = delete;
		ObjectManager& operator=(const ObjectManager&) = delete;
	};

}
