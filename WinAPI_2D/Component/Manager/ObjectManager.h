#pragma once
#include "Manager.h"
#include "PoolManager.h"
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

		template <class ClassType, typename... Args>
		ClassType* Spawn(Args&&... InArgs)
		{
			std::unique_ptr<ClassType> pooledObj = PoolManager<ClassType>::Get().Spawn(std::forward<Args>(InArgs)...);
			ClassType*                 rawPtr    = pooledObj.get();
			mManagedList.try_emplace(pooledObj->GetName(), std::move(pooledObj));

			return rawPtr;
		}

		template <class ClassType>
		void DeSpawn(ClassType* InObj)
		{
			const WText objName = InObj->GetName();
			if (ClassType* rawPtr = dynamic_cast<ClassType*>(mManagedList[objName].release()))
			{
				mManagedList.erase(objName);
				std::unique_ptr<ClassType> ptr(rawPtr);
				PoolManager<ClassType>::Get().DeSpawn(std::move(ptr));
			}
			// else
			// {
			// 	mManagedList[objName].reset(rawPtr);
			// }
		}

		bool DestroyObject(const WText& InObjName);

	private:
		friend class TSingleton<ObjectManager>;
		ObjectManager()  = default;
		~ObjectManager() = default;

	public:
		ObjectManager(const ObjectManager&)            = delete;
		ObjectManager& operator=(const ObjectManager&) = delete;
	};

}
