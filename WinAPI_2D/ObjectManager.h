#pragma once
#include "CommonInclude.h"

namespace LJG
{
	CLASS_PTR(ObjectManager)

	class ObjectManager : public ICoreAPI
	{
	public:
		void Initialize() override;
		void Update(float DeltaTime) override;
		void Render() override;
		void Release() override;

		inline static ObjectManager& Get()
		{
			static ObjectManager instance;
			return instance;
		}

		template <class ReturnType, typename... Args>
		ReturnType* CreateObject(WTextView InKey, Args&&... InArgs)
		{
			static_assert(std::is_base_of_v<UObject, ReturnType>, L"UObject에서 파생되어야함");

			std::unique_ptr<ReturnType> obj    = std::make_unique<ReturnType>(std::forward<Args>(InArgs)...);
			ReturnType*                 rawPtr = obj.get();
			mManagedObjects[WText(InKey)]      = std::move(obj);

			return rawPtr;
		}

	private:
		void RemoveInvalidObjects();

	private:
		// Resize Callback
		void OnResizeCallback(UINT InWidth, UINT InHeight);

	private:
		std::unordered_map<WText, UObjectUPtr> mManagedObjects;

	private:
		ObjectManager()           = default;
		~ObjectManager() override = default;

	public:
		ObjectManager(const ObjectManager&)            = delete;
		ObjectManager& operator=(const ObjectManager&) = delete;

	};
}
