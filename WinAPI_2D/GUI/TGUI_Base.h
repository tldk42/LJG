#pragma once
#include "../CommonInclude.h"

namespace LJG
{
	class USceneComponent;

	class TGUI_Base : public ICoreAPI
	{
	public:
		TGUI_Base(HWND InWindowHandle);

	public:
#pragma region Core Interface
		void Initialize() override;
		void Update(float DeltaTime) override;
		void Render() override;
		void Release() override;
#pragma endregion

		void BindSceneComponent(USceneComponent* InBindObject);

	protected:
		HWND mWindowHandle;

		USceneComponent* mObjectToShow;
	};
}
