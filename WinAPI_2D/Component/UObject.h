#pragma once
#include "CommonInclude.h"
#include "Component/Manager/ObjectManager.h"

namespace LJG
{
	class UObject : public ICoreAPI
	{
	public:
		explicit UObject();
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

		inline AActor* GetOwnerActor() const { return mOwnerActor; }
		inline void    SetOwnerActor(AActor* InActor) { mOwnerActor = InActor; }

		template <class ReturnType, typename... Args>
		ReturnType* CreateDefaultSubObject(const WText& InName, Args&&... args)
		{
			static_assert(std::is_base_of_v<UObject, ReturnType>, L"UObject���� ��� �޾ƾ� ��");

			std::unique_ptr<ReturnType> managedPtr = std::make_unique<ReturnType>(InName, std::forward<Args>(args)...);
			ReturnType*                 rawPtr     = managedPtr.get();
			mChildObjects.try_emplace(InName, std::move(managedPtr));

			return rawPtr;
		}

		void AttachComponent(UObject* ComponentToAttach);
		void SetupAttachment(UObject* InParentObj);
		void DettachComponent();

		void DontDestroyOnLoad(const bool bEnable) { bDontDestroyOnLoad = bEnable; }

	protected:
		WText   mObjectKey;			// ���� Ű
		AActor* mOwnerActor;			// ������Ʈ ���� ���� 
		bool    bDontDestroyOnLoad; // �� �̵��� ����?
		/*  �ڽ� ������Ʈ (�� ��ü�� �ٴ� ���� �������� �� ������Ʈ�� ����) Update,Render, ��� �� ���Ϳ��� ���� */
		std::unordered_map<WText, UObjectUPtr> mChildObjects;

	private:
		friend class ObjectManager;
	};
}
