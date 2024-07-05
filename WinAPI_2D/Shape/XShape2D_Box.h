#pragma once
#include "DirectX/XVertex2D.h"


namespace LJG
{
	/** */
	class XShape2D_Box : public XVertex2D
	{
	public:
		XShape2D_Box();
		~XShape2D_Box() override = default;

		void Render() override;

	protected:
		HRESULT LoadShaderAndInputLayout() override;
	};
}
