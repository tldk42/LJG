#define CRTDBG_MAP_ALLOC       // 메모리 누수 확인용
#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <cstdlib>             // 메모리 누수 확인용
#include <crtdbg.h>             // 메모리 누수 확인용

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
                   LPSTR     lpCmdLine, int       nShowCmd)
{
	// 디버그 빌드시 메모리 누수 체크
#if defined(DEBUG) | defined(_DEBUG)
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif

	MSG winMsg;


}
