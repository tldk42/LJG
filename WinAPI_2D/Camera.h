#pragma once
#include "Component/Actor/AActor.h"

namespace LJG
{
	class XProjectionBuffer;
	class XViewBuffer;

	class ACamera : public AActor
	{
	public:
		explicit ACamera(const WText& InKey);
		~ACamera() override;

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

		float mZoom;
	};
}
