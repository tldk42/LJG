#include "PoolManager.h"
//
// #include "Game/Object/Game_2/Enemy/FrogProjectile.h"
//
// std::unique_ptr<LJG::FrogProjectile> LJG::FrogProjectileManager::Spawn(EGame2Projectile Type)
// {
// 	if (mPoolObjects.empty())
// 	{
// 		for (size_t i = 0; i < mMaxPoolSize; ++i)
// 		{
// 			mPoolObjects.emplace_back(std::make_unique<FrogProjectile>(Type));
// 		}
// 	}
// 	std::unique_ptr<FrogProjectile> obj = std::move(mPoolObjects.back());
// 	obj->SetActive(true);
// 	mPoolObjects.pop_back();
// 	return obj;
// }
