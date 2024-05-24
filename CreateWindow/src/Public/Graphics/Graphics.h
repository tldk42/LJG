#pragma once

namespace LJG
{
	static bool  FULL_SCREEN   = false;
	static bool  VSYNC_ENABLED = true;
	static float SCREEN_DEPTH  = 1000.0f;
	static float SCREEN_NEAR   = 0.1f;

	class Graphics
	{
	public:
		Graphics();
		~Graphics() = default;

		HRESULT Initialize();

		void Clear();

		HRESULT Render();
	};
}
