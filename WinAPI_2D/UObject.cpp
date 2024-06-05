#include "UObject.h"

#include "UTexture.h"


namespace LJG
{
	UObject::UObject() {}

	UObject::UObject(const std::wstring& InTextureFile)
	{
		if (!InTextureFile.empty())
		{
			mVertexMesh = new UTexture(InTextureFile);
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

	void UObject::SetTextureResource(const std::wstring& InTextureFile, const bool bForceModify)
	{
		if (!mVertexMesh || bForceModify)
		{
			mVertexMesh = new UTexture(InTextureFile);
		}
	}
}
