#pragma once
#include "CommonInclude.h"

namespace LJG
{
	class XShaderData;


#pragma region Data
	struct FVertexBase
	{
		FVector3f    Pos;
		FVector2f    Tex;
		FLinearColor Color;
	};
#pragma endregion

	/**
	 * \brief 2D전용 메시 정점이 항상 4개 고정
	 */
	class XVertex2D : public ICoreAPI
	{
	public:
		XVertex2D(const float InZOrder = 0.f);
		~XVertex2D() override;

	public:
#pragma region Core Interface
		void Initialize() override;
		void Update(float DeltaTime) override;
		void Render() override;
		void Release() override;
#pragma endregion

	public:
#pragma region Set
		virtual void SetColor(const FLinearColor& InColor);
		virtual void SetScale(const FVector2f& InScale);
		virtual void SetWorldRotation(const float InDegree);
		virtual void SetWorldLocation(const FVector2f& InLocation);
		virtual void AddWorldLocation(const FVector2f& InAddLocation);
		virtual void SetWorldTransform(const Matrix& InMatrix);
		virtual void SetWorldTransform(const FVector2f& InLocation, const float InAngle, const FVector2f& InScale);
		virtual void SetFlipX(const bool bEnable);
#pragma endregion

#pragma region Get
		inline const FVector2f& GetLocation() const { return Mat2LocVector2(mTransform); }
		inline const FVector2f& GetScale() const { return Mat2ScaleVector2(mTransform); }
#pragma endregion

	protected:
		HRESULT CreateShape();
		HRESULT CreateVertexBuffer();
		HRESULT CreateIndexBuffer();
		HRESULT LoadShaderAndInputLayout();

		virtual void CreateVertexArray();
		virtual void CreateIndexArray();

		void SetShaderParams() const;

		virtual void OnResizeCallback();

	protected:
#pragma region Buffer & Layout
		ComPtr<ID3D11InputLayout> mVertexLayout;
		ComPtr<ID3D11Buffer>      mVertexBuffer;
		ComPtr<ID3D11Buffer>      mIndexBuffer;
		XWorldBufferUPtr          mWorldBuffer;
		D3D_PRIMITIVE_TOPOLOGY    mPrimType;
		FLinearColor              mDrawColor;
		std::vector<FVertexBase>  mVertexBufferArray;
		std::vector<WORD>         mIndices;
#pragma endregion

#pragma region Shader
		XShaderData* mShaderData;
#pragma endregion

#pragma region Transform
		Matrix mTransform = XMMatrixIdentity();
#pragma endregion

		FVector2f mTextureScale;
		float     mZOrder = 0.f;
		bool      bFlipX  = false;
	};
}
