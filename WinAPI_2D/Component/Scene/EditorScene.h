#pragma once
#include "UScene.h"

namespace LJG
{
	class EditorScene : public UScene
	{
	public:
		void LoadScene() override;
		void EndScene() override;

		
	};
}
