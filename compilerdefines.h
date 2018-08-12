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

#define C_DECL_CONSTEXPR 
#define CT_DECL_CONSTEXPR  C_DECL_CONSTEXPR

//define namespace start
#ifndef BEGIN_NAMESPACE
#define BEGIN_GLOBAL_NAMESPACE namespace Ct {
#define END_GLOBAL_NAMESPACE }
#else
#undef BEGIN_NAMESPACE
#define BEGIN_NAMESPACE(name) namespace name{
#endif

#define CT_DECLARE_FLAGS(Flags, Enum)\
typedef CFlags<Enum> Flags;

#include <new>

typedef wchar_t wchar;

#include <iostream>
#define _wstream_operator_insertion(_class, _ty)\
static inline const _class &operator<<(const _class &debug, _ty var)\
{ std::wcout << var; return debug; }

#define _define_wchar_operator_insertion(_class, _ty) _wstream_operator_insertion(_class,_ty)

#define _stream_operator_insertion(_class, _ty)\
static inline const _class &operator<<(const _class &debug, _ty var)\
{ std::cout << var; return debug; }

#define _define_char_operator_insertion(_class, _ty) _stream_operator_insertion(_class,_ty)

#include <ctime>
#include <cstdarg>
#include <cstdio>

static void debug_log(const char * fmt, ...)
{
	std::time_t t = std::time(nullptr);
	char time_buf[100];
#ifdef _MSC_VER 
#if (_MSC_VER>=1900)
	tm _tm; gmtime_s(&_tm, &t);
	std::strftime(time_buf, sizeof time_buf, "%D %T", &_tm);
#endif // (_MSC_VER>1900)
#else
	std::strftime(time_buf, sizeof time_buf, "%D %T", gmtime(&t));
#endif
	va_list args1;
	va_start(args1, fmt);
	va_list args2;
	va_copy(args2, args1);
	std::string buf;
	buf.resize(std::vsnprintf(NULL, 0, fmt, args1) + 1);
	va_end(args1);
	std::vsnprintf(const_cast<char*>(buf.data()), buf.size(), fmt, args2);
	va_end(args2);
	std::printf("%s [debug]: %s\n", time_buf, buf.data());
}

#define LOG(fmt,...) debug_log(fmt,_VAR_ARGS_)
//#define C_DECLARE_OPERATORS_FOR_FLAGS(Flags) \
//C_DECL_CONSTEXPR inline CFlags<Flags::enum_type> operator|(Flags::enum_type f1, Flags::enum_type f2) __nothrow \
//{ return CFlags<Flags::enum_type>(f1) | f2; } \
//C_DECL_CONSTEXPR inline CFlags<Flags::enum_type> operator|(Flags::enum_type f1, CFlags<Flags::enum_type> f2) __nothrow \
//{ return f2 | f1; } Q_DECLARE_INCOMPATIBLE_FLAGS(Flags)