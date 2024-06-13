#include <DirectXMath.h>

#include "Application_Base.h"

int main()
{
	using namespace LJG;

	FWindowData testWindowData;
	{
		testWindowData.Width       = 1024;
		testWindowData.Height      = 768;
		testWindowData.bFullScreen = false;
		testWindowData.bVsync      = false;
	}


	// ----------------------- START ------------------------------
	{
		Application_Base app(L"Renderer", testWindowData);
		app.Start();
	}
	return 0;
}
