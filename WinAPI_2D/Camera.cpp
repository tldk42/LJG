#include "Camera.h"

#include "InputManager.h"
#include "Window.h"
#include "DirectX/Context.h"


namespace LJG
{

	ACamera::ACamera()
		: AActor(L"MainCam"),
		  mZoom(1.f),
		  mCameraSpeed(300.f)
	{
		mViewMatrix       = XMMatrixIdentity();
		mProjectionMatrix = XMMatrixIdentity();
	}


	void ACamera::Initialize()
	{
		AActor::Initialize();

		Window::GetWindow()->OnResize.Bind([&](UINT InWidth, UINT InHeight){
			SetProjection(InWidth, InHeight);
		});

		SetProjection(Context::GetViewportSize().X, Context::GetViewportSize().Y);

		mViewBuffer       = std::make_unique<XViewBuffer>();
		mProjectionBuffer = std::make_unique<XProjectionBuffer>();
	}

	void ACamera::Update(float DeltaTime)
	{
		AActor::Update(DeltaTime);

		if (InputManager::IsKeyPressed(EKeyCode::I))
		{
			AddWorldLocation(FVector2f{0.f, 200.f} * DeltaTime);
		}
		if (InputManager::IsKeyPressed(EKeyCode::K))
		{
			AddWorldLocation(FVector2f{0.f, -200.f} * DeltaTime);

		}
		if (InputManager::IsKeyPressed(EKeyCode::J))
		{
			AddWorldLocation(FVector2f{-200.f, 0.f} * DeltaTime);

		}
		if (InputManager::IsKeyPressed(EKeyCode::L))
		{
			AddWorldLocation(FVector2f{200.f, 0.f} * DeltaTime);
		}

		UpdateViewMatrix();
		mProjectionBuffer->SetProjectionMatrix(mProjectionMatrix);
		mViewBuffer->SetViewMatrix(mViewMatrix);
		
		mProjectionBuffer->Update(DeltaTime);
		mViewBuffer->Update(DeltaTime);
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
		if (InScreenWidth > M_SMALL_NUMBER && InScreenHeight > M_SMALL_NUMBER)
			mProjectionMatrix = XMMatrixOrthographicOffCenterLH(
				-InScreenWidth / 2.f, InScreenWidth / 2.f,
				-InScreenHeight / 2.f, InScreenHeight / 2.f, 0.f, 1.f);
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
