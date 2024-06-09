#include "UObject.h"

#include "USprite2D.h"


namespace LJG
{
	UObject::UObject() {}

	UObject::UObject(const std::wstring& InTextureFile)
	{
		if (!InTextureFile.empty())
		{
			mVertexMesh.reset(new USprite2D(InTextureFile));
		}
	}

	UObject::~UObject()
	{
		UObject::Release();
	}

	void UObject::Initialize() {}

	void UObject::Update(float DeltaTime)
	{
		mVertexMesh->Update(DeltaTime);
	}

	void UObject::Render()
	{
		mVertexMesh->Render();
	}

	void UObject::Release()
	{
		mVertexMesh->Release();
	}

	void UObject::SetLocation(const FVector2f& InLocation) const
	{
		mVertexMesh->SetWorldLocation(InLocation);
	}

	FVector2f UObject::GetLocation() const
	{
		return FVector2f::ZeroVector;
	}

	void UObject::SetTextureResource(const std::wstring& InTextureFile, const bool bForceModify)
	{
		if (!mVertexMesh || bForceModify)
		{
			mVertexMesh.reset(new USprite2D(InTextureFile));
		}
	}

	void UObject::OnResize()
	{
		mVertexMesh->OnResizeCallback();
	}
}
