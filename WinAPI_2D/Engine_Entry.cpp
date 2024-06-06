#include "Application_Base.h"
#include "InputManager.h"
#include "UObject.h"
#include "ObjectManager.h"
#include "PlayerController.h"


int main()
{
	using namespace LJG;

	FWindowData testWindowData;
	testWindowData.Width       = 1024;
	testWindowData.Height      = 768;
	testWindowData.bFullScreen = false;
	testWindowData.bVsync      = false;

	Application_Base app(L"Renderer", testWindowData);
	ObjectManager::AddObject(new UObject(L"background.jpg"));
	ObjectManager::AddObject(new PlayerController(L"jacob.jpg"));
	app.Start();

	return 0;
}
