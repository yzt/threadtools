#pragma once
//======================================================================

#include <atomic>
#include <cstdint>
#include <utility>

//======================================================================

namespace PY {
	namespace WORM {

//======================================================================
	
template <typename T>
class Singleton
{
private:
	struct Wrapper
	{
		T * ptr;
		int64_t ref_cnt;
		
		Wrapper () = delete;
	};
	
public:
	template <typename... Types>
	explicit Singleton (Types &&... args)
		: m_current {new Wrapper{new T {std::forward<Types>(args)...}, 1}}
	{
	}
	
private:
	Wrapper * m_current = nullptr;
};

//----------------------------------------------------------------------

template <typename T>
class Reader
{
	
};

//----------------------------------------------------------------------

template <typename T>
class Writer
{
	
};

//----------------------------------------------------------------------
//======================================================================

	}	// namespace WORM
}	// namespace PY

//======================================================================
