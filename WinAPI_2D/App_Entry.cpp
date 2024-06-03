#include "Application_Base.h"
#include "DXWrite.h"
#include "Object.h"

int main()
{
	using namespace LJG;

	FWindowData testWindowData;
	testWindowData.Width       = 1024;
	testWindowData.Height      = 768;
	testWindowData.bFullScreen = false;
	testWindowData.bVsync      = false;

	Application_Base* testApp = new Application_Base(L"Sample Renderer", testWindowData);
	if (testApp)
	{
		testApp->Initialize();

		FWriteData IntroText({
			                     testWindowData.Width / 2 - 36, testWindowData.Height / 2 - 36,
			                     testWindowData.Width, testWindowData.Height
		                     }, L"샘플");
		DXWrite::AddText(&IntroText);

		testApp->Start();
	}


	return 0;
}
