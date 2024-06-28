#pragma once
#include "DirectX/XVertex2D.h"

namespace LJG
{
	class XShape2D_Line : public ICoreAPI
	{
	public:
		XShape2D_Line();
		~XShape2D_Line() override;

	public:
#pragma region Core Interface
		void Initialize() override;
		void Update(float DeltaTime) override;
		void Render() override;
		void Release() override;
#pragma endregion

#pragma region Set
		virtual void SetColor(const FLinearColor& InColor);
		virtual void SetScale(const FVector2f& InScale);
		virtual void SetWorldRotation(const float InDegree);
		virtual void SetWorldLocation(const FVector2f& InLocation);
		virtual void AddWorldLocation(const FVector2f& InAddLocation);
		virtual void SetWorldTransform(const Matrix& InMatrix);
		virtual void SetWorldTransform(const FVector2f& InLocation, const float InAngle, const FVector2f& InScale);
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
	};
}
