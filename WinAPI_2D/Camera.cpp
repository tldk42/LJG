#include "Camera.h"

#include "DirectX/XProjectionBuffer.h"
#include "DirectX/XViewBuffer.h"

namespace LJG
{
	ACamera::ACamera()
		: mZoom(1.f)
	{
		mViewMatrix       = XMMatrixIdentity();
		mProjectionMatrix = XMMatrixIdentity();

		ACamera::Initialize();
	}

	ACamera::~ACamera()
	{
	}

	void ACamera::Initialize()
	{
		AActor::Initialize();

		mViewBuffer       = std::make_unique<XViewBuffer>();
		mProjectionBuffer = std::make_unique<XProjectionBuffer>();
	}

	void ACamera::Update(float DeltaTime)
	{
		AActor::Update(DeltaTime);

		UpdateViewMatrix();

		mViewBuffer->SetViewMatrix(mViewMatrix);
		mViewBuffer->Update(DeltaTime);

		mProjectionBuffer->SetProjectionMatrix(mProjectionMatrix);
		mProjectionBuffer->Update(DeltaTime);
	}

	void ACamera::Render()
	{
		AActor::Render();

		mViewBuffer->Render();
		mProjectionBuffer->Render();
	}

	void ACamera::Release()
	{
		AActor::Release();

		mViewBuffer       = nullptr;
		mProjectionBuffer = nullptr;
	}

	void ACamera::SetProjection(float InScreenWidth, float InScreenHeight)
	{
		mProjectionMatrix = XMMatrixOrthographicOffCenterLH(-InScreenWidth / 2.f, InScreenWidth / 2.f,
		                                                    -InScreenHeight / 2.f, InScreenHeight / 2.f, -1.f, 1.f);
	}

	void ACamera::SetPosition(const FVector2f& InPosition)
	{
		SetWorldLocation(InPosition);
	}

	void ACamera::SetZoom(float InZoom)
	{
		mZoom = InZoom;
		UpdateViewMatrix();
	}

	void ACamera::UpdateViewMatrix()
	{
		mViewMatrix = XMMatrixTranslation(-GetWorldLocation().X, -GetWorldLocation().Y, 0.f) *
			XMMatrixScaling(mZoom, mZoom, 1.f);
	}
}
