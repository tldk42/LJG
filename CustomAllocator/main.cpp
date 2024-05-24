
#include <algorithm>
#include <limits>

template <typename T>
class CustomAlloc
{
public:
	template <typename U>
	struct rebind
	{
		using other = CustomAlloc<U>;
	};

public:
	using TValue = T;

	using Pointer = T*;
	using ConstPointer = const T*;

	using VoidPointer = void*;
	using ConstVoidPointer = const void*;

	using SizeType = size_t;

	using DifferenceType = std::ptrdiff_t;

public:
	CustomAlloc() = default;
	~CustomAlloc() = default;

	void test()
	{
		operator new (sizeof(T) * 1);
		std::transform
	}
};