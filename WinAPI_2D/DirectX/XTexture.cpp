#include "XTexture.h"
#include <directxtk/WICTextureLoader.h>
#include "Context.h"
#include "Helper/UDXHelper.h"

namespace LJG
{

	XTexture::XTexture(const WText& InKey, UINT InSlot)
		: mSlot(InSlot),
		  mKey(InKey),
		  mSRVDesc(),
		  mTextureDesc()
	{
		XTexture::Initialize();
	}

	XTexture::~XTexture()
	{
		XTexture::Release();
	}

	void XTexture::Initialize()
	{
		if (!mKey.empty())
		{
			CHECK_RESULT(DirectX::CreateWICTextureFromFile(Context::GetDevice(), mKey.c_str(),
														   mTextureResource.GetAddressOf(),
														   mSRV.GetAddressOf()));
			CHECK_RESULT(mTextureResource->QueryInterface(__uuidof(ID3D11Texture2D),
														  reinterpret_cast<void**>(mTexture.GetAddressOf())));

			// 텍스처 정보 가져오기
			mSRV->GetDesc(&mSRVDesc);
			mTexture->GetDesc(&mTextureDesc);

			std::string texName;
			texName.assign(mKey.begin(), mKey.end());
			LOG_DX_INFO("File: {}", texName);
		}
	}

	void XTexture::Update(float DeltaTime) {}
	
	void XTexture::Render()
	{
		Context::GetDeviceContext()->PSSetShaderResources(mSlot, 1, mSRV.GetAddressOf());
	}

	void XTexture::Release()
	{
		mTextureResource = nullptr;
		mSRV             = nullptr;
		mTexture         = nullptr;
	}
}
