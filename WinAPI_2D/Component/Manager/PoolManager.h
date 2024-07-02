#pragma once
#include "Manager.h"

namespace LJG
{
	template <class ClassType>
	class PoolManager : public ICoreAPI
	{
	public:
		PoolManager();
		~PoolManager() override;

#pragma region Core Interface
		void Initialize() override
		{
			mObjects.reserve(mMaxPoolSize);
		}

		void Update(float DeltaTime) override
		{
			for (std::unique_ptr<ClassType>& obj : mObjects)
			{
				obj->Update(DeltaTime);
			}
		}

		void Render() override
		{
			for (std::unique_ptr<ClassType>& obj : mObjects)
			{
				obj->Render();
			}
		}

		void Release() override
		{
			for (std::unique_ptr<ClassType>& obj : mObjects)
			{
				obj->Release();
			}
		}
#pragma endregion

	protected:
		int32_t                                 mMaxPoolSize = 20.f;
		std::vector<std::unique_ptr<ClassType>> mObjects;
	};


	class ProjectileManager : public PoolManager<ProjectileManager>, public TSingleton<ProjectileManager>
	{};
}
