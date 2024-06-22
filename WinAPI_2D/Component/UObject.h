#pragma once
#include "CommonInclude.h"
#include "Component/Manager/ObjectManager.h"

namespace LJG
{
	class UObject : public ICoreAPI
	{
	public:
		explicit UObject(const WText& InKey);
		explicit UObject(AActor* InOwnerActor);
		~UObject() override;

	public:
#pragma region Core Interface
		void Initialize() override;
		void Update(float DeltaTime) override;
		void Render() override;
		void Release() override;
#pragma endregion

		inline AActor*  GetOwnerActor() const { return mOwnerActor; }
		inline UObject* GetParent() const { return mParentObject; }
		inline void     SetOwnerActor(AActor* InActor) { mOwnerActor = InActor; }

		template <class ReturnType, typename... Args>
		ReturnType* CreateDefaultSubObject(const WText& InName, Args&&... args)
		{
			return Manager_Object.Load<ReturnType>(InName, std::forward<Args>(args)...);
		}

		void AttachComponent(UObject* ComponentToAttach);
		void SetupAttachment(UObject* InParentObj);

	protected:
		WText                               mObjectKey;
		AActor*                             mOwnerActor;
		UObject*                            mParentObject;
		std::unordered_map<WText, UObject*> mChildObjects;

	private:
		friend class ManagerBase<UObject, ObjectManager>;
	};
}
