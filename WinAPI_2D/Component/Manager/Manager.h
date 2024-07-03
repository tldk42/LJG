#pragma once

#include "CommonInclude.h"

namespace LJG
{
#define ManagerTemplate template<typename ReturnType, class ClassType>

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

	ManagerTemplate
	class ManagerBase : public TSingleton<ClassType>
	{
	public:
		// 사용자 지정 생성
		template <class ReturnClass = ReturnType, typename... Args>
		ReturnClass* CreateOrLoad(const WText& InName, Args&&... InArgs);

		template <class ReturnClass = ReturnType>
		ReturnClass* GetResource(const WText& InName);

		void TrySafeRemove(const WText& InName);

	protected:
		[[nodiscard]] static WText SplitPath(const WText& InPath, const WText& InEntry = L"");
		void                       RemoveInvalidResource();

	protected:
		std::unordered_map<WText, std::unique_ptr<ReturnType>> mManagedList;
	};

	ManagerTemplate
	template <class ReturnClass, typename... Args>
	ReturnClass* ManagerBase<ReturnType, ClassType>::CreateOrLoad(const WText& InName, Args&&... InArgs)
	{
		// 경로일 경우 구분하고 아닐 경우 그대로
		WText id = SplitPath(InName);

		if (ReturnClass* resource = GetResource<ReturnClass>(id))
		{
			return resource;
		}

		std::unique_ptr<ReturnClass> obj    = std::make_unique<ReturnClass>(InName, std::forward<Args>(InArgs)...);
		ReturnClass*                 rawPtr = obj.get();
		mManagedList.try_emplace(id, std::move(obj));

		return rawPtr;
	}

	ManagerTemplate
	template <class ReturnClass = ReturnType>
	ReturnClass* ManagerBase<ReturnType, ClassType>::GetResource(const WText& InName)
	{
		static_assert(std::is_base_of_v<ReturnType, ReturnClass>, L"타입 불일치");

		if (mManagedList.contains(InName))
		{
			return static_cast<ReturnClass*>(mManagedList[InName].get());
		}

		WText maybeID = SplitPath(InName);
		if (mManagedList.contains(maybeID))
		{
			return static_cast<ReturnClass*>(mManagedList[maybeID].get());
		}
		return nullptr;
	}

	template <typename ReturnType, class ClassType>
	void ManagerBase<ReturnType, ClassType>::TrySafeRemove(const WText& InName)
	{
		if (mManagedList.contains(InName))
		{
			mManagedList.erase(InName);
		}
	}

	ManagerTemplate
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

	ManagerTemplate
	void ManagerBase<ReturnType, ClassType>::RemoveInvalidResource()
	{
		// mManagedList.erase(
		// 	std::remove_if(
		// 		mManagedList.begin(),
		// 		mManagedList.end(),
		// 		[](std::pair<WText, std::unique_ptr<ReturnType>>& obj){ return obj.second == nullptr; }),
		// 	mManagedList.end());
	}
}
