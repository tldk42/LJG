#include "Application_Base.h"

int main()
{
	using namespace LJG;

	FWindowData testWindowData;
	testWindowData.Width       = 900;
	testWindowData.Height      = 600;
	testWindowData.bFullScreen = false;
	testWindowData.bVsync      = false;

	Application_Base* testApp = new Application_Base(L"Sample Renderer", testWindowData);
	if (testApp)
	{
		testApp->Start();
	}


	return 0;
}
