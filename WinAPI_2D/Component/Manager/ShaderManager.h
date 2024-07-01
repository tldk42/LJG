#pragma once
#include "Manager.h"

namespace LJG
{
	#define Manager_Shader ShaderManager::Get()

	class XShaderData;

	class ShaderManager : public ManagerBase<XShaderData, ShaderManager>
	{
	private:
		friend class TSingleton<ShaderManager>;
		ShaderManager()  = default;
		~ShaderManager() = default;

	public:
		ShaderManager(const ShaderManager&)            = delete;
		ShaderManager& operator=(const ShaderManager&) = delete;
	};
}
