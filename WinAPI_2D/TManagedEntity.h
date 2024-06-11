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
		// ���ο� ��ü ������ ������ Create�� ��ŷ
		template <typename... Args>
		static std::shared_ptr<T> Create(Args&&... args)
		{
			return std::make_shared<T>(std::forward<Args>(args)...);
		}

		// new�� delete ����� ���ƹ�����
		[[deprecated("���������")]] void* operator new(size_t)   = delete;
		[[deprecated("������")]] void    operator delete(void*) = delete;
	};
}
