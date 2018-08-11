#ifndef UTILITY_DEF_H
#define UTILITY_DEF_H

#include <utility>

#ifndef _T
#define _T(s) L##s
#endif

#include <string>
#include <String>
#include <cstdint>
#include <algorithm>

static std::wstring to_wstring(std::string s) {
	std::wstring t(s.length(), _T(' '));
	std::copy(s.begin(), s.end(), t.begin());
	return t;
}

static inline bool isNull(float f)
{
	union U {
		float f;
		uint32_t u;
	};
	U val;
	val.f = f;
	return (val.u & 0x7fffffff) == 0;
}

static inline bool fuzzyIsNull(float f)
{
	return abs(f) <= 0.00001f;
}


#endif //UTILITY_DEF_H