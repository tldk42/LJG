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

		inline bool    IsActive() const { return bActive; }
		inline bool    IsPoolManagedComponent() const { return bIsPoolManaged; }
		inline WText   GetName() const { return mObjectKey; }
		inline AActor* GetOwnerActor() const { return mOwnerActor; }
		inline void    SetOwnerActor(AActor* InActor) { mOwnerActor = InActor; }

		template <class ReturnType, typename... Args>
		ReturnType* CreateDefaultSubObject(Args&&... args)
		{
			static_assert(std::is_base_of_v<UObject, ReturnType>, L"UObject���� ��� �޾ƾ� ��");

			std::unique_ptr<ReturnType> managedPtr = std::make_unique<ReturnType>(std::forward<Args>(args)...);
			ReturnType*                 rawPtr     = managedPtr.get();
			mChildObjects.try_emplace(rawPtr->GetName(), std::move(managedPtr));

			return rawPtr;
		}

		void SetActive(const bool bActivate)
		{
			bActive = bActivate;
			for (auto& obj : mChildObjects)
			{
				obj.second->bActive = bActivate;
			}
		}

		void Destroy() const;

		void AttachComponent(UObject* ComponentToAttach);
		void SetupAttachment(UObject* InParentObj);
		void DettachComponent();

		void DontDestroyOnLoad(const bool bEnable) { bDontDestroyOnLoad = bEnable; }

	protected:
		WText   mObjectKey;			// ���� Ű
		AActor* mOwnerActor;			// ������Ʈ ���� ���� 
		bool    bDontDestroyOnLoad; // �� �̵��� ����?
		bool    bActive        = true;
		bool    bIsPoolManaged = false;

		/*  �ڽ� ������Ʈ (�� ��ü�� �ٴ� ���� �������� �� ������Ʈ�� ����) Update,Render, ��� �� ���Ϳ��� ���� */
		std::unordered_map<WText, UObjectUPtr> mChildObjects;

	private:
		friend class ObjectManager;
	};

	#define CreateSprite(str) CreateDefaultSubObject<USpriteAnimation>(str)
}
