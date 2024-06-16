#pragma once
#include "CommonInclude.h"
#include "ObjectManager.h"

namespace LJG
{
	class UObject : public ICoreAPI
	{
	public:
		UObject();
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
		ReturnType* CreateDefaultSubObject(WTextView InKey, Args&&... args)
		{
			return ObjectManager::Get().CreateObject<ReturnType>(InKey, std::forward<Args>(args)...);
		}

		void AttachComponent(UObject* ComponentToAttach);
		void SetupAttachment(UObject* InParentObj);

	protected:
		WText                               mObjectID;
		AActor*                             mOwnerActor;
		UObject*                            mParentObject;
		std::unordered_map<WText, UObject*> mChildObjects;

	private:
		void SetID(WTextView InID) { mObjectID = InID; }
		friend class ObjectManager;
	};
}
