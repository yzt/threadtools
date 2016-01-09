#pragma once
//======================================================================

#include <new>		// placement new
#include <utility>	// std::forward

//======================================================================

namespace PY {

//======================================================================

class Allocator
{
public:
	virtual void * alloc (size_t bytes/*, size_t align, size_t align_offset*/) = 0;
	virtual void free (void * ptr, size_t bytes) = 0;

public:
	template <typename T, typename... ArgTypes>
	T * create (ArgTypes&&... args)
	{
		auto p = static_cast<T *>(alloc(sizeof(T)));
		if (nullptr != p)
			new (p) T (std::forward<ArgTypes>(args)...);
		return p;
	}

	template <typename T, typename... ArgTypes>
	T * createArray (size_t N, ArgTypes&&... args)
	{
		auto p = static_cast<T *>(alloc(N * sizeof(T)));
		if (nullptr != p)
		{
			size_t i = 0;
			try {
				for ( ; i < N; ++i)
					new (p + i) T (std::forward<ArgTypes>(args)...);
			}
			catch (...) {
				i += 1;
				for ( ; i > 0; --i)
					(p + i - 1)->T::~T();
				throw;
			}
		}
		return p;
	}

	template <typename T>
	void destroy (T * ptr)
	{
		if (nullptr != ptr)
		{
			ptr->T::~T();
			free(ptr);
		}
	}

	template <typename T>
	void destroyArray (T * ptr, size_t N)
	{
		if (nullptr != ptr)
		{
			for (size_t i = N; i > 0; --i)
				ptr[i - 1]->T::~T();
			free(ptr);
		}
	}
};

//======================================================================

class HeapAllocator
	: public Allocator
{
public:
	HeapAllocator () = default;
	HeapAllocator (HeapAllocator const &) = default;
	HeapAllocator (HeapAllocator &&) = default;
	HeapAllocator & operator = (HeapAllocator const &) = default;
	HeapAllocator & operator = (HeapAllocator &&) = default;

	virtual void * alloc (size_t bytes) override;
	virtual void free (void * ptr, size_t bytes) override;

private:
};

//======================================================================
//----------------------------------------------------------------------
//======================================================================

}	// namespace PY

//======================================================================
