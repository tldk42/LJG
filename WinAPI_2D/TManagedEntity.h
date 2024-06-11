#pragma once

#include <memory>

namespace LJG
{
	template <class T>
	class TManagedEntity
	{
	protected:
		TManagedEntity()  = default;
		~TManagedEntity() = default;

	public:
		// 새로운 개체 생성은 무조건 Create로 패킹
		template <typename... Args>
		static std::shared_ptr<T> Create(Args&&... args)
		{
			return std::make_shared<T>(std::forward<Args>(args)...);
		}

		// new와 delete 사용을 막아버리기
		[[deprecated("사용하지마")]] void* operator new(size_t)   = delete;
		[[deprecated("쓰지마")]] void    operator delete(void*) = delete;
	};
}
