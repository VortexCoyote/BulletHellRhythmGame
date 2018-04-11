#ifndef HEADER_MATH
#define HEADER_MATH

namespace Math
{
	template<typename T>
	inline T Lerp(T v0, T v1, T t)
	{
		return (1 - t)*v0 + t*v1;
	}
}

#endif

