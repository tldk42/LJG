#include "UObject.h"

#include "XSprite2D.h"


namespace LJG
{
	UObject::UObject() {}

	UObject::UObject(AActorSPtr InOwnerActor)
	{}

	UObject::~UObject()
	{
		UObject::Release();
	}

	void UObject::Initialize() {}

	void UObject::Update(float DeltaTime)
	{}

	void UObject::Render()
	{}

	void UObject::Release()
	{}


}
