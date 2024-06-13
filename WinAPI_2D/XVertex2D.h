#pragma once
#include <DirectXMath.h>
#include "CommonInclude.h"

namespace LJG
{
	struct FVertexBase
	{
		FVector2f    Pos;
		FVector2f    Tex;
		FLinearColor Color;
	};

	using namespace DirectX;

	// 이동 변환 행렬 생성
	inline XMMATRIX TranslationMatrix(float tx, float ty)
	{
		return XMMatrixTranslation(tx, ty, 0.0f);
	}

	// 회전 변환 행렬 생성
	inline XMMATRIX RotationMatrix(float angle)
	{
		float radians = XMConvertToRadians(angle);
		return XMMatrixRotationZ(radians);
	}

	// 스케일 변환 행렬 생성
	inline XMMATRIX ScaleMatrix(float sx, float sy)
	{
		return XMMatrixScaling(sx, sy, 1.0f);
	}

	/**
	 * \brief 2D전용 메시 정점이 항상 4개 고정
	 */
	class XVertex2D : public ICoreAPI
	{
	public:
		XVertex2D();
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
		void SetWindowResolution();
		void SetColor(const FLinearColor& InColor);
		void SetScale(const FVector2f& InScale);
		void SetWorldRotation(const float InAngle);
		void SetWorldLocation(const FVector2f& InLocation);
		void AddWorldLocation(const FVector2f& InAddLocation);
		void SetWorldTransform(const FVector2f& InLocation, const float InAngle, const FVector2f& InScale);
#pragma endregion

	protected:
		HRESULT CreateShape();
		HRESULT CreateVertexBuffer();
		HRESULT CreateIndexBuffer();
		HRESULT LoadShaderAndInputLayout();

		virtual void CreateVertexArray();
		virtual void CreateIndexArray();

		void SetShaderParams() const;

		void NDC2Screen();
		void Screen2NDC();
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
		FVector2f mScale              = FVector2f::UnitVector;
		FVector2f mWorldLocation      = FVector2f::ZeroVector;
		FVector2f mNDCLocation        = FVector2f::ZeroVector;
		FVector2f mNDCOffset          = FVector2f::ZeroVector;
		FVector2f mNormalizedLocation = FVector2f::ZeroVector;
		FVector2f mScreenResolution;
		float     mAngle = 0.f;
#pragma endregion

		FLinearColor           mDrawColor;
		D3D_PRIMITIVE_TOPOLOGY mPrimType;
	};
}
