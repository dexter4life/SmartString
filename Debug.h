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

