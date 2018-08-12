/*
This software is provided 'as-is', without any express or
implied warranty. In no event will the authors be held
liable for any damages arising from the use of this software.

Permission is granted to anyone to use this software for any purpose,
including commercial applications, and to alter it and redistribute
it freely, subject to the following restrictions:

1. The origin of this software must not be misrepresented;
you must not claim that you wrote the original software.
If you use this software in a product, an acknowledgment
in the product documentation would be appreciated but
is not required.

2. Altered source versions must be plainly marked as such,
and must not be misrepresented as being the original software.

3. This notice may not be removed or altered from any
source distribution.

Author: Peter Nwanosike
Email:dexter4life@gmail.com
*/
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