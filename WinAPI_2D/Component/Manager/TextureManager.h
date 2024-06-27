#pragma once
#include "Manager.h"
#include "DirectX/XTexture.h"

namespace LJG
{
	#define Manager_Texture TextureManager::Get()

	class TextureManager : public ManagerBase<XTexture, TextureManager>
	{
	private:
		friend class TSingleton<TextureManager>;
		TextureManager()  = default;
		~TextureManager() = default;

	public:
		TextureManager(const TextureManager&)            = delete;
		TextureManager& operator=(const TextureManager&) = delete;
	};

}
