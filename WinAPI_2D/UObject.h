#pragma once
#include "CommonInclude.h"

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

		void      SetLocation(const FVector2f& NewLocation) const;
		FVector2f GetLocation() const;

	public:
		void SetTextureResource(const std::wstring& InTextureFile, const bool bForceModify);

	protected:
		UTextureUPtr mVertexMesh;
	};
}
