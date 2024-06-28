#pragma once
#include "Component/Actor/AActor.h"
#include "DirectX/XProjectionBuffer.h"
#include "DirectX/XViewBuffer.h"

namespace LJG
{
	#define MainCam ACamera::Get()

	class ACamera : public AActor, public TSingleton<ACamera>
	{
	public:
#pragma region Core Interface
		void Initialize() override;
		void Update(float DeltaTime) override;
		void Render() override;
		void Release() override;
#pragma endregion

#pragma region Set
		void SetProjection(float InScreenWidth, float InScreenHeight);
		void SetPosition(const FVector2f& InPosition);
		void SetZoom(float InZoom);
#pragma endregion

		[[nodiscard]] XMMATRIX GetViewMatrix() const { return mViewMatrix; }
		[[nodiscard]] XMMATRIX GetProjectionMatrix() const { return mProjectionMatrix; }

	private:
		void UpdateViewMatrix();

	private:
		Matrix mViewMatrix;
		Matrix mProjectionMatrix;

		XViewBufferUPtr       mViewBuffer;
		XProjectionBufferUPtr mProjectionBuffer;

		float_t mZoom;
		float_t mCameraSpeed;

	private:
		friend class TSingleton<ACamera>;

		ACamera();
		~ACamera() = default;

	public:
		ACamera(const ACamera&)            = delete;
		ACamera& operator=(const ACamera&) = delete;
	};
}
