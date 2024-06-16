#pragma once
#include "CommonInclude.h"

namespace LJG
{
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
		void SetColor(const FLinearColor& InColor);
		void SetScale(const FVector2f& InScale);
		void SetWorldRotation(const float InAngle);
		void SetWorldLocation(const FVector2f& InLocation);
		void AddWorldLocation(const FVector2f& InAddLocation);
		void SetWorldTransform(const FVector2f& InLocation, const float InAngle, const FVector2f& InScale);
		void SetFlipX(const bool bEnable);
#pragma endregion

#pragma region Get
		inline const FVector2f& GetLocation() const { return mWorldLocation; }
		inline const FVector2f& GetScale() const { return mScale; }
#pragma endregion

	protected:
		HRESULT CreateShape();
		HRESULT CreateVertexBuffer();
		HRESULT CreateIndexBuffer();
		HRESULT LoadShaderAndInputLayout();

		virtual void CreateVertexArray();
		virtual void CreateIndexArray();

		void SetShaderParams() const;

		void SetTransform(const FVector2f& InLocation, const float InAngle, const FVector2f& InScale);

		virtual void OnResizeCallback();

	protected:
#pragma region Buffer & Layout
		ComPtr<ID3D11InputLayout> mVertexLayout;
		ComPtr<ID3D11Buffer>      mVertexBuffer;
		ComPtr<ID3D11Buffer>      mIndexBuffer;
		std::vector<FVertexBase>  mVertexBufferArray;
		std::vector<WORD>         mIndices;
#pragma endregion

#pragma region Shader
		ComPtr<ID3D11VertexShader> mVertexShader;
		ComPtr<ID3D11PixelShader>  mPixelShader;
#pragma endregion

#pragma region Transform
		FVector2f mWorldLocation = FVector2f::ZeroVector;
		float     mAngle         = 0.f;
		FVector2f mScale         = FVector2f::UnitVector;
#pragma endregion

		float mZOrder = 0.f;

		XWorldBufferUPtr mWorldBuffer;

		FLinearColor           mDrawColor;
		D3D_PRIMITIVE_TOPOLOGY mPrimType;

		bool bFlipX = false;
	};
}
