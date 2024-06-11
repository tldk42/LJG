#include "UDebugShape2D.h"

namespace LJG
{
	UDebugShape2D::UDebugShape2D()
	{
		mPrimType  = D3D11_PRIMITIVE_TOPOLOGY_LINELIST;
		mDrawColor = FLinearColor(0, 1.f, 0, 1.f);
	}
	
}
