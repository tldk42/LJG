#include "XTexture.h"
#include <directxtk/WICTextureLoader.h>
#include "Context.h"
#include "UDXHelper.h"

namespace LJG
{

	XTexture::XTexture(const std::wstring& InFile, UINT InSlot)
		: mSlot(InSlot),
		  mFilePath(InFile),
		  mSRVDesc(),
		  mTextureDesc()
	{}

	XTexture::~XTexture()
	{
		XTexture::Release();
	}

	void XTexture::Initialize()
	{
		if (!mFilePath.empty())
		{
			CHECK_RESULT(DirectX::CreateWICTextureFromFile(Context::GetDevice(), mFilePath.c_str(),
														   mTextureResource.GetAddressOf(),
														   mSRV.GetAddressOf()));
			CHECK_RESULT(mTextureResource->QueryInterface(__uuidof(ID3D11Texture2D),
														  reinterpret_cast<void**>(mTexture.GetAddressOf())));

			// 텍스처 정보 가져오기
			mSRV->GetDesc(&mSRVDesc);
			mTexture->GetDesc(&mTextureDesc);

			LOG_DX_INFO("-------- Texure Loaded ----------");
			std::string texName;
			texName.assign(mFilePath.begin(), mFilePath.end());
			LOG_DX_INFO("File: {}", texName);
			LOG_DX_INFO("Width: {}", mTextureDesc.Width);
			LOG_DX_INFO("Height: {}", mTextureDesc.Height);
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
