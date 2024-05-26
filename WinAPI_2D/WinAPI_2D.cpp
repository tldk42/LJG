#include "App.h"

#pragma region Graphic Initialize
#include <d3d11.h>


/* 링커 연결
* 1. 속성 -> 링커 -> 입력 -> 추가종속성
* 2. #pragma comment(lib, libName)*/


bool CreateDevice(HWND Hwnd)
{
	ID3D11Device*        g_D3dDevice;
	ID3D11DeviceContext* g_D3dDeviceContext;
	IDXGISwapChain*      g_SwapChain;

	ID3D11RenderTargetView* g_D3dRTV;

	D3D_FEATURE_LEVEL    g_FeatureLevel = D3D_FEATURE_LEVEL_11_0;
	DXGI_SWAP_CHAIN_DESC swapChainDesc; // SwapChainDesc 채워줘야 함
	ZeroMemory(&swapChainDesc, sizeof(swapChainDesc));

	swapChainDesc.BufferCount                        = 1;
	swapChainDesc.BufferDesc.Width                   = 1600;                            // Buffer Width
	swapChainDesc.BufferDesc.Height                  = 900;                             // Buffer Height
	swapChainDesc.BufferDesc.Format                  = DXGI_FORMAT_R8G8B8A8_UNORM;      // 색상 출력 형식
	swapChainDesc.BufferDesc.RefreshRate.Numerator   = 60;                              // FPS 분자
	swapChainDesc.BufferDesc.RefreshRate.Denominator = 1;                               // FPS 분모
	swapChainDesc.BufferUsage                        = DXGI_USAGE_RENDER_TARGET_OUTPUT; // 버퍼 (렌더링 버퍼)
	swapChainDesc.OutputWindow                       = Hwnd;                            // 출력될 윈도우 핸들
	swapChainDesc.SampleDesc.Count                   = 1;                               // 멀티 샘플링 개수
	swapChainDesc.SampleDesc.Quality                 = 0;                               // 멀티 샘플링 품질
	swapChainDesc.Windowed                           = true;                            // 창 전체 화면 모드
	swapChainDesc.SwapEffect                         = DXGI_SWAP_EFFECT_DISCARD;
	swapChainDesc.Flags                              = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;


	if (FAILED(D3D11CreateDeviceAndSwapChain(
		NULL,                               // pAdapter (모니터) : null이면 주 모니터 사용
		D3D_DRIVER_TYPE_HARDWARE,           // 하드웨어 가속 사용
		NULL,                               // 소프트웨어로 구동? (하드웨어 사용시 NULL)
		D3D11_CREATE_DEVICE_SINGLETHREADED, // 디버그 계층 활성화
		&g_FeatureLevel,                    // DX 기능 수준
		1,                                  // 배열 원소
		D3D11_SDK_VERSION,                  // DX SDK Version
		&swapChainDesc,                     // SwapChain 구조체 정보
		&g_SwapChain,
		&g_D3dDevice, // 생성한 장치
		NULL,
		&g_D3dDeviceContext // 생성된 장치 컨텍스트
	)))
	{
		return false;
	}

	if (g_D3dDevice && g_SwapChain)
	{
		ID3D11Resource*               g_D3dResource = nullptr;
		D3D11_RENDER_TARGET_VIEW_DESC RTVDesc;

		g_D3dDevice->CreateRenderTargetView(g_D3dResource, &RTVDesc, &g_D3dRTV);
	}


	return true;
};
void DeleteDevice();
#pragma endregion

int main()
{
	using namespace LJG;

	FWindowData testWindowData;
	testWindowData.Width       = 900;
	testWindowData.Height      = 600;
	testWindowData.bFullScreen = false;
	testWindowData.bVsync      = true;

	App* testApp = new App(L"Test Window", testWindowData);
	if (testApp)
	{
		testApp->Start();
	}


	return 0;
}
