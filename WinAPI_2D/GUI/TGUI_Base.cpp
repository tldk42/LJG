#include "TGUI_Base.h"
#include "imgui.h"
#include "imgui_impl_win32.h"
#include "imgui_impl_dx11.h"
#include "DirectX/Context.h"

namespace LJG
{

	TGUI_Base::TGUI_Base(HWND InWindowHandle)
		: mWindowHandle(InWindowHandle)
	{}

	void TGUI_Base::Initialize()
	{
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();

		ImGuiIO& io = ImGui::GetIO();


		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
		io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;         // IF using Docking Branch

		ImGui_ImplWin32_Init(mWindowHandle); // WindowHandle Instance (창마다 도킹 할 창이 다를 수 있음)
		ImGui_ImplDX11_Init(Context::GetDevice(), Context::GetDeviceContext()); // Device, DeviceContext
	}

	void TGUI_Base::Update(float DeltaTime)
	{
		ImGui_ImplDX11_NewFrame();
		ImGui_ImplWin32_NewFrame();
		ImGui::NewFrame();

		// TODO: 여기에 GUI 기능을 구현
		// ImGui::ShowDemoWindow();
	}

	void TGUI_Base::Render()
	{
		ImGui::Render();
		ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
	}

	void TGUI_Base::Release()
	{
		ImGui_ImplDX11_Shutdown();
		ImGui_ImplWin32_Shutdown();
		ImGui::DestroyContext();
	}

	void TGUI_Base::BindSceneComponent(USceneComponent* InBindObject)
	{
		mObjectToShow = InBindObject;
	}

}
