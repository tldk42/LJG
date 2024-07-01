#include "Application.h"

using namespace LJG;
FWindowData testWindowData;

int main()
{
	testWindowData.Width       = 1280;
	testWindowData.Height      = 720;
	testWindowData.bFullScreen = false;
	testWindowData.bVsync      = false;

	// ----------------------- START ------------------------------

	App.Start();


	return 0;
}
