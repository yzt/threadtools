
#include <worm_singleton.hpp>

int main ()
{
	auto x = PY::WORM::Singleton<int>(42);
	
	return 0;
}