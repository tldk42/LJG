#pragma once

#include "CommonInclude.h"

namespace LJG
{
	template <class ClassType>
	class TSingleton
	{
	public:
		[[nodiscard]] static ClassType& Get()
		{
			static ClassType instance;
			return instance;
		}
	};


	template <typename ReturnType, class ClassType>
	class ManagerBase : public TSingleton<ClassType>
	{
	public:
		template <class ReturnClass = ReturnType, typename... Args>
		ReturnClass* Load(const WText& InName, Args&&... InArgs);
		template <class ReturnClass = ReturnType>
		ReturnClass* GetResource(const WText& InName);

	protected:
		[[nodiscard]] static WText SplitPath(const WText& InPath, const WText& InEntry = L"");
		void                       RemoveInvalidResource();

	protected:
		std::unordered_map<WText, std::unique_ptr<ReturnType>> mManagedList;
	};

	template <typename ReturnType, class ClassType>
	template <class ReturnClass, typename... Args>
	ReturnClass* ManagerBase<ReturnType, ClassType>::Load(const WText& InName, Args&&... InArgs)
	{
		// static_assert(std::is_base_of_v<IManagedAPI, ReturnClass>, L"ManagedAPI에서 상속 받아야 함");

		// 경로일 경우 구분하고 아닐 경우 그대로
		WText id = SplitPath(InName);

		if (ReturnClass* resource = GetResource<ReturnClass>(id))
		{
			return resource;
		}

		std::unique_ptr<ReturnClass> obj    = std::make_unique<ReturnClass>(InName, std::forward<Args>(InArgs)...);
		ReturnClass*                 rawPtr = obj.get();
		mManagedList.emplace(id, std::move(obj));

		return rawPtr;
	}

	template <typename ReturnType, class ClassType>
	template <class ReturnClass = ReturnType>
	ReturnClass* ManagerBase<ReturnType, ClassType>::GetResource(const WText& InName)
	{
		static_assert(std::is_base_of_v<ReturnType, ReturnClass>, L"타입 불일치");

		if (mManagedList.contains(InName))
		{
			return static_cast<ReturnClass*>(mManagedList[InName].get());
		}

		return nullptr;
	}

	template <typename ReturnType, class ClassType>
	WText ManagerBase<ReturnType, ClassType>::SplitPath(const WText& InPath, const WText& InEntry)
	{
		wchar_t drive[MAX_PATH]      = {0,};
		wchar_t directory[MAX_PATH]  = {0,};
		wchar_t fileName[MAX_PATH]   = {0,};
		wchar_t fileExtent[MAX_PATH] = {0,};

		_tsplitpath_s(InPath.c_str(), drive, directory, fileName, fileExtent);

		WText key = fileName;
		key.append(fileExtent);

		if (!InEntry.empty())
		{
			key.append(InEntry);
		}

		return key;
	}

	template <typename ReturnType, class ClassType>
	void ManagerBase<ReturnType, ClassType>::RemoveInvalidResource()
	{
		for (auto it = mManagedList.begin(); it != mManagedList.end();)
		{
			if (!it->second)
			{
				it = mManagedList.erase(it);
			}
			else
			{
				++it;
			}
		}
	}
}
