#pragma once
#include "CommonInclude.h"

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

	protected:
		AActor* mOwnerActor;

	private:
		friend class ObjectManager;


	};
}
