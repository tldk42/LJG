#pragma once
#include "CommonInclude.h"
#include "UTexture.h"

namespace LJG
{
	class UObject : public ICoreAPI
	{
	public:
		UObject();
		UObject(const std::wstring& InTextureFile);
		~UObject();

	public:
#pragma region Core Interface
		void Initialize() override;
		void Update(float DeltaTime) override;
		void Render() override;
		void Release() override;
#pragma endregion

		inline void      SetLocation(const FVector2f& NewLocation) const { mVertexMesh->SetWorldLocation(NewLocation); }
		inline FVector2f GetLocation() const { return mVertexMesh->GetWorldLocation(); }

	public:
		void SetTextureResource(const std::wstring& InTextureFile, const bool bForceModify);

	protected:
		class UTexture* mVertexMesh;
	};
}
