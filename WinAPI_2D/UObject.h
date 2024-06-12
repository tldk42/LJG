#pragma once
#include "CommonInclude.h"
#include "ObjectManager.h"

namespace LJG
{
	class UObject : public ICoreAPI
	{
	public:
		UObject();
		explicit UObject(AActorSPtr InOwnerActor);
		~UObject() override;

	public:
#pragma region Core Interface
		void Initialize() override;
		void Update(float DeltaTime) override;
		void Render() override;
		void Release() override;
#pragma endregion

		inline AActor* GetOwnerActor() const { return mOwnerActor; }
		void           SetOwnerActor(AActor* InActor) { mOwnerActor = InActor; }

		template <class ReturnType, typename... Args>
		ReturnType* CreateDefaultSubObject(WTextView InKey, Args&&... args)
		{
			return ObjectManager::Get().CreateObject<ReturnType>(InKey, std::forward<Args>(args)...);
		}

	protected:
		AActor* mOwnerActor;

	private:
		friend class ObjectManager;
	};
}
