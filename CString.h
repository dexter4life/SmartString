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
#ifndef CT_STRING_H
#define CT_STRING_H

#include <string>
#include <iosfwd>
#include <map>
#include <string>
#include <locale>
#include <codecvt>
#include <iostream>
#include <cassert>
#include <algorithm>

#include "utilitydef.h"
#include "global.h"
#include "Debug.h"

#ifdef _MSC_VER 
#if !(_MSC_VER > 1800) 
#error compiler version is lesser than required.  
#endif
#endif

#define IsSpace(c) std::isspace(c,loc)

class RegExp;
using std::char_traits;
using std::allocator;

class String : public std::wstring
{
	friend static const std::wostream& operator<<(std::wostream &wo, const String &s) {
		wo << std::wstring(s.c_str());
		return wo;
	}
	friend static std::ostream& operator<<(std::ostream &wo, const String &s) {
		std::wstring_convert<std::codecvt_utf8<wchar_t>> conv1;
		std::string u8str = conv1.to_bytes(s);
		wo << u8str;
		return wo;
	}
public:
	typedef typename std::wstring std_string_type;
	typedef typename std::string std_cstring_type;
	typedef const wchar_t * _wchar_t;
	typedef uint32_t uint;

	String() {};
	~String() { clear(); };

	explicit String(const String &s)
	{
		assign(s.data());
	}
	String(const std::wstring &s) : std::wstring(s)
	{
	}
	String(const std::string &s)
	{
		assign(to_wstring(s));
	}
	String(std::string s)
	{
		assign(to_wstring(s));
	}
	String(size_t _bufferCount, wchar_t c = L' ')
	{
		resize(_bufferCount);
		std::fill(begin(), end(), c);
	}
	String(const_iterator _first, const_iterator _last)
	{
		assign(_first, _last);
	}
	String(const wchar_t *s)
	{
		assign(s);
	}
	String(const char *s)
	{
		assign(to_wstring(s));
	}
	//return wide-character 
	operator std_string_type ()
	{
		return std_string_type(c_str());
	}
	//return multi-byte charactor
	operator std_cstring_type()
	{
		std_cstring_type _result; _result.resize(length());
		size_t _length = length();
#ifdef _MSC_VER 
		size_t _iNumberCharConverted = 0;
		wcstombs_s(&_iNumberCharConverted, const_cast<char*>(_result.data()), _length + 1, c_str(), _length * sizeof(wchar));
#else
	std:wcstombs(const_cast<char*>(_result.data()), c_str(), length());
#endif
		return _result;
	}
	//make wchar_t *
	operator _wchar_t()
	{
		return c_str();
	}
	void String::operator=(const String s)
	{
		assign(s.c_str());
	}
	std::wstring to_wstring(int64_t value)
	{
		return to_wstring(std::to_string(value));
	}
	std::wstring to_wstring(const std::string &s)
	{
		std::wstring t(s.length(), L' ');
		std::copy(s.begin(), s.end(), t.begin());
		return t;
	}

	String tolower() const;
	String toupper() const;

	int indexOf(wchar c, int from = 0, Ct::CaseSensitivity cs = Ct::CaseSensitive) const;
	int indexOf(const String &s, int from = 0, Ct::CaseSensitivity cs = Ct::CaseSensitive) const;

	int lastIndexOf(wchar c, int from = -1, Ct::CaseSensitivity cs = Ct::CaseSensitive) const;
	int lastIndexOf(const String &s, int from = -1, Ct::CaseSensitivity cs = Ct::CaseSensitive) const;

	bool contains(wchar c, Ct::CaseSensitivity cs = Ct::CaseSensitive) const;
	bool contains(const String &s, Ct::CaseSensitivity cs = Ct::CaseSensitive) const;
	inline bool contains(const RegExp &rx) const { return indexOf(rx) != -1; }

	int count(wchar c, Ct::CaseSensitivity cs = Ct::CaseSensitive) const;
	int count(const String &, Ct::CaseSensitivity cs = Ct::CaseSensitive) const;
	int count(const RegExp &rex) const;


	int indexOf(const RegExp &rex, int from = 0) const;

	/*
	lastIndexOf(String str) : This method accepts a String as an argument,
	if the string argument occurs one or more times as a substring within this object,
	then the index of the first character of the last such substring is returned.
	If it does not occur as a substring, -1 is returned.
	*/
	//int lastIndexOf(const RegExp &rex, int from = -1, int count = 0) const;

	String mid(int position, int offset = -1) const;

	/*
	//!  replace
	// Replace substring that match regular expression 'rex 
	// rex Regular Expression
	// fmt Formating string or replacement string
	// cs  Case sensitivity flags ( case-sensitive or insentive)
	*/
	bool replace(const RegExp &rex, const String &fmt, Ct::CaseSensitivity cs = Ct::CaseSensitive);
	bool replace(const String & oldVal, const String & newVal);
	bool replace(const wchar_t oldVal, const wchar_t newVal, size_t offset = 0);

	/*
	//! formatString 
	// Format string into string object 
	// s Formatting string
	// returns new formated string
	*/
	static String formatString(String s, ...);
	void	 appendFormat(String fmt, ...);

	//compare in case sensitivity
	bool isequal(const String & right, Ct::CaseSensitivity cs = Ct::CaseSensitive);
	
	//compare locale
	int compare_l(const String & Input, const std::locale &loc = std::locale());
	
	/*
	Trim
	Remove all leading and trailing spaces from the input.
	The input sequence is modified in-place.

	\param offset Starting position from left to right
	*/
	void	 trim(int offset = 0);

	/* contains_l
	//Search string for matching substring. 
	//Elements are compared case sensitively.
	//\param Test A test sequence
	//\param Loc A locale used for case insensitive comparison
	//\return The result of the test
	*/
	bool contains_l(
		const String& Test,
		const std::locale& Loc = std::locale());
	inline void trim_right(String & Input, int offset = 0)
	{
		Input.erase(trim_end(Input.begin(), std::prev(Input.end(), offset)), Input.end());
	}

	/*!
	Remove all leading spaces from the input.

	\param Input An input sequence
	\param IsSpace A unary predicate identifying spaces
	*/
	inline void trim_left(String &Input, int offset = 0)
	{
		Input.erase(std::next(Input.begin(), offset), trim_begin(Input.begin(), Input.end()));
	}

	/*
	//! is_equal
	//  Check if two characters are equal based on locale
	//\param offset An input character from String object
	//\test character to compare
	//\loc locale to use or default is taken
	*/
	bool isequal_l(int offset, String::value_type test,
		const std::locale &loc = std::locale())
	{
		return isequal_l(at(offset), test, loc);
	}

	/*
	//This predicate holds when the test string is a prefix of the Input.
	//In other words, if the input starts with the test.
	//When the optional predicate is specified, it is used for character-wise
	//comparison.
	//
	//\param Input An input sequence
	//\param Test A test sequence
	//\param loc An locale element
	//\return The result of the test
	*/
	bool starts_with(
		const String& Input,
		const String& Test,
		const std::locale &loc = std::locale());

	/*
	//This predicate holds when the test string is a prefix of the Input.
	//In other words, if the input starts with the test.
	//When the optional predicate is specified, it is used for character-wise
	//comparison.
	//
	//\param Test A test sequence
	//\param loc An locale element
	//\return The result of the test
	*/
	inline bool starts_with(
		const String& Test,
		const std::locale &loc = std::locale())
	{ return starts_with(*this, Test, loc); }
	
	/*
	//This predicate holds when the test string is a suffix of the Input.
	//In other words, if the input ends with the test.
	//When the optional predicate is specified, it is used for character-wise
	//comparison.
	//
	//
	//\param	Input An input sequence
	//\param	Test A test sequence
	//\param	loc An element of locale
	//\return	The result of the test
	*/
	bool ends_with(
		const String& Input,
		const String& Test,
		const std::locale &loc = std::locale());

	/*
	//! is_equal
	//  Check if two characters are equal based on locale
	*/
	bool isequal_l(String::value_type input,
		String::value_type test, const std::locale &loc = std::locale());
private:

	// Search for first non matching character from the beginning of the sequence
	inline iterator trim_begin(
		iterator InBegin,
		iterator InEnd);

	// Search for first non matching character from the end of the sequence
	inline iterator trim_end(
		iterator InBegin,
		iterator InEnd);
	//void     Truncate(int nNewLength);
	std::locale loc;
};

// string list container
#ifndef STRING_LIST
#include <vector>
typedef std::vector<String> StringList;

//display to output stream
static std::wostream& operator<<(std::wostream &wo, const StringList &stringList)
{
	wo << String("{");
	size_t i = 0;
	for (const String &is : stringList) {
		wo << is;
		if (i++ < stringList.size() - 1) wo << ",";
	}
	wo << String("}");
	return wo;
}
typedef std::vector<std::wstring> WideStringList;

//display to output stream
static inline const Debug &operator<<(const Debug &debug, WideStringList &stringList)
{
	std::wcout << "{";
	auto _begin = stringList.begin();
	while (_begin != stringList.end()) {
		std::wcout << (*_begin);
		if (std::next(_begin, 1) != stringList.end())
			std::wcout << L",";
		++_begin;
	}
	std::wcout << "}";
	return debug;
}

_define_wchar_operator_insertion(Debug, const StringList &)
_define_wchar_operator_insertion(Debug, String)

typedef std::vector<std::wstring> wstring_list;
static void insert_item(StringList& list, const wstring_list &item_list)
{
	std::for_each(item_list.begin(), item_list.end(), [&](auto item) {
		list.push_back(String(item));
	});
}
//insertion operator 
static StringList &operator<<(StringList &stringList, const String &str) {
	stringList.push_back(str);
	return stringList;
}


#endif // !STRING_LIST

#endif // !STRING_H
