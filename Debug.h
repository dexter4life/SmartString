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

#pragma once
#ifdef _DEBUG
#ifndef CT_DEBUG_H
#define CT_DEBUG_H

#include <iostream>
#include <iterator>
#include <algorithm>
#include <vector>
#include <string>
#include "compilerdefines.h"

class Debug
{
public:
	typedef const wchar_t * const_wchart;

	friend _define_wchar_operator_insertion(Debug,int)
	friend _define_wchar_operator_insertion(Debug, size_t)
	friend _define_wchar_operator_insertion(Debug, double)
	friend _define_wchar_operator_insertion(Debug, float)
	friend _define_wchar_operator_insertion(Debug, const_wchart)
	friend _define_wchar_operator_insertion(Debug, std::wstring)
	friend _define_char_operator_insertion(Debug, const char)
	friend _define_wchar_operator_insertion(Debug, const wchar)

public:
	Debug();
	~Debug();
};

#endif
static Debug debug;
#if defined(UNICODE) || defined(_UNICODE)
#define NEW_LINE L"\n";
#if NODEBUG
#else
#define _debugl(_param_) debug<<_param_<<NEW_LINE
#define debugl(n) _debugl(n)
#endif
#else
#define NEW_LINE "\n";
#endif // 



#endif // !CT_DEBUG_H

