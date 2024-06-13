#include "XDebugShape2D.h"
#include "../Context.h"
#include "../XVertex2D.h"

namespace LJG
{
	XDebugShape2D::XDebugShape2D()
	{
		mPrimType  = D3D11_PRIMITIVE_TOPOLOGY_LINELIST;
		mDrawColor = FLinearColor(0, 1.f, 0, 1.f);
	}

	void XDebugShape2D::Render()
	{
		XVertex2D::Render();
		Context::GetDeviceContext()->DrawIndexed(8, 0, 0);
	}
}
