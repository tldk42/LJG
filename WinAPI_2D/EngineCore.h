#pragma once
#include "Application_Base.h"
#include "CommonInclude.h"

namespace LJG
{
	class EngineCore : public Application_Base, ICoreAPI
	{
	public:
		EngineCore() = delete;
		EngineCore(LPCWSTR WindowTitle, const FWindowData& WindowData);

	public:
#pragma region Core Interface
		void Initialize() override;
		void Update() override;
		void Render() override;
		void Release() override;
#pragma endregion

		void Run() override;

		static inline EngineCore* GetGEngine() { return s_Engine; }

	private:
		static EngineCore* s_Engine;
	};
}
