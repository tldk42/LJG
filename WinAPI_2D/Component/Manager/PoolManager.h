#pragma once
#include <memory>
#include <vector>

#include "Manager.h"

namespace LJG
{
	class AProjectile;

	template <class ClassType>
	class PoolManager : public TSingleton<PoolManager<ClassType>>
	{
	public:
		PoolManager();
		~PoolManager();

		template <typename... Args>
		std::unique_ptr<ClassType> Spawn(Args&&... InArgs);

		void DeSpawn(std::unique_ptr<ClassType> Object);

	protected:
		int32_t                                 mMaxPoolSize = 20.f;
		std::vector<std::unique_ptr<ClassType>> mPoolObjects;
	};

	template <class ClassType>
	PoolManager<ClassType>::PoolManager()
	{}

	template <class ClassType>
	PoolManager<ClassType>::~PoolManager() {}

	template <class ClassType>
	template <typename... Args>
	std::unique_ptr<ClassType> PoolManager<ClassType>::Spawn(Args&&... InArgs)
	{
		if (mPoolObjects.empty())
		{
			for (size_t i = 0; i < mMaxPoolSize; ++i)
			{
				mPoolObjects.emplace_back(std::make_unique<ClassType>(std::forward<Args>(InArgs)...));
				mPoolObjects[i]->SetActive(false);
			}
		}
		std::unique_ptr<ClassType> obj = std::move(mPoolObjects.back());
		obj->SetActive(true);
		mPoolObjects.pop_back();
		return obj;
	}

	template <class ClassType>
	void PoolManager<ClassType>::DeSpawn(std::unique_ptr<ClassType> Object)
	{
		Object->SetActive(false);
		mPoolObjects.emplace_back(std::move(Object));
	}

	class ProjectileManager : public PoolManager<AProjectile>
	{};
}
