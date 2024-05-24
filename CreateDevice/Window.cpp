#include "Window.h"

namespace LJG
{
	bool  Window::InitializeWindow(HINSTANCE hInstance)
	{
		mHinstance = hInstance;

		CreateRegisterClass();
	}
}