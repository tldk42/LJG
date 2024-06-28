#include "XShape2D_Box.h"
#include "DirectX/Context.h"
#include "DirectX/XVertex2D.h"

namespace LJG
{
	XShape2D_Box::XShape2D_Box()
	{
		mZOrder    = 0.1f;
		mPrimType  = D3D11_PRIMITIVE_TOPOLOGY_LINELIST;
		mDrawColor = FLinearColor(0, 1.f, 0, 1.f);
	}

	void XShape2D_Box::Render()
	{
		XVertex2D::Render();
		Context::GetDeviceContext()->DrawIndexed(8, 0, 0);
	}
}
