#include "XShape2D_Box.h"

#include "Component/Manager/ShaderManager.h"
#include "DirectX/Context.h"
#include "DirectX/XVertex2D.h"
#include "DirectX/XShaderData.h"


namespace LJG
{
	XShape2D_Box::XShape2D_Box()
	{
		mZOrder    = 0.15f;
		mPrimType  = D3D11_PRIMITIVE_TOPOLOGY_LINELIST;
		mDrawColor = {0, 1, 0, 1};
	}

	void XShape2D_Box::Render()
	{
		XVertex2D::Render();

		Context::GetDeviceContext()->DrawIndexed(8, 0, 0);
	}


	HRESULT XShape2D_Box::LoadShaderAndInputLayout()
	{
		HRESULT result = S_OK;

		mShaderData = Manager_Shader.CreateOrLoad(L"SimpleShader", L"Shader/simple.vsh", L"Shader/simple.psh");

		return result;

	}
}
