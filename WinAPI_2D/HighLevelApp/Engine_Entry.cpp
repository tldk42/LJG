#include "Application.h"

using namespace LJG;
FWindowData testWindowData;

int main()
{
	testWindowData.Width       = 1024;
	testWindowData.Height      = 768;
	testWindowData.bFullScreen = false;
	testWindowData.bVsync      = false;

	// ----------------------- START ------------------------------

	App.Start();


	return 0;
}
