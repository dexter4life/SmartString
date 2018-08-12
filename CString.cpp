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
#include "CString.h"
#include "RegExp.h"
#include <cstdarg>

#include <cwctype>

String String::tolower() const
{
	String _lowerstring = *this;
	std::transform(_lowerstring.begin(), _lowerstring.end(), _lowerstring.begin(), ::tolower);
	return _lowerstring;
}

String String::toupper() const
{
	String _upperstring = *this;
	std::transform(_upperstring.begin(), _upperstring.end(), _upperstring.begin(), ::toupper);
	return _upperstring;
}

int String::indexOf(wchar c, int from, Ct::CaseSensitivity cs) const
{
	//assume if not found
	size_t pos = std::wstring::npos;

	if (cs == Ct::CaseInsensitive) {
		if (std::iswupper(c) && std::iswalpha(c)) {
			wint_t lc = std::towlower(c);
			String tp = *this;
			std::transform(tp.begin(), tp.end(), tp.begin(), ::tolower);
			pos = tp.find(lc, (size_t)from);
			return pos;
		}
	}
	//everthing else goes here
	pos = this->find(c, (size_t)from);
	return (int)pos;
}

int String::indexOf(const String & s, int from, Ct::CaseSensitivity cs) const
{
	//assume if not found
	size_t pos = std::wstring::npos;
	if (cs == Ct::CaseInsensitive) {
		String tp = tolower(), ta = s.tolower();
		pos = tp.find(ta, (size_t)from);
		return pos;
	}
	pos = find(s, from);
	return pos;
}

int String::lastIndexOf(wchar c, int from, Ct::CaseSensitivity cs) const
{
	//assume if not found
	size_t pos = std::wstring::npos;

	if (cs == Ct::CaseInsensitive) {
		if (std::iswupper(c) && std::iswalpha(c)) {
			wint_t lc = std::towlower(c);
			String tp = *this;
			std::transform(tp.begin(), tp.end(), tp.begin(), ::tolower);
			pos = tp.find_last_of(lc, (size_t)from);
			return pos;
		}
	}
	//everthing else goes here
	pos = this->find_last_of(c, (size_t)from);
	return (int)pos;
}

int String::lastIndexOf(const String & s, int from, Ct::CaseSensitivity cs) const
{
	//assume if not found
	size_t pos = std::wstring::npos;
	if (cs == Ct::CaseInsensitive) {
		String tp = *this, ta = s;
		std::transform(tp.begin(), tp.end(), tp.begin(), ::tolower);
		std::transform(ta.begin(), ta.end(), ta.begin(), ::tolower);
		pos = tp.find_last_of(ta, (size_t)from);
		return pos;
	}
	pos = find_last_of(s, from);
	return pos;
}

bool String::contains(wchar c, Ct::CaseSensitivity cs) const
{
	int pos = indexOf(c, 0, cs);
	return (pos != std::string::npos);
}

bool String::contains(const String & s, Ct::CaseSensitivity cs) const
{
	int pos = indexOf(s, 0, cs);
	return (pos != std::string::npos);
}

int String::count(wchar c, Ct::CaseSensitivity cs) const
{
	int _count = 0;
	if (cs == Ct::CaseInsensitive) {
		if (std::iswupper(c) && std::iswalpha(c)) {
			wint_t lc = std::towlower(c);
			String ta = *this;
			std::transform(ta.begin(), ta.end(), ta.begin(), ::tolower);
			std::for_each(ta.begin(), ta.end(), [&](wchar ac) {
				if (ac == c) _count++;
			});
		}
		return _count;
	}
	std::for_each(begin(), end(), [&](wchar ac) {
		if (ac == c) _count++;
	});
	return _count;
}

int String::count(const String & s, Ct::CaseSensitivity cs) const
{
	// Get the first occurrence
	size_t pos = indexOf(s, 0, cs);

	int _count = 0;
	// Repeat till end is reached
	while (pos != std::string::npos)
	{
		// Add position to the vector
		_count++;
		// Get the next occurrence from the current position
		pos = indexOf(s, pos + s.size(), cs);
	}

	return _count;
}

int String::indexOf(const RegExp &ex, int from) const
{
	return ex.indexIn(*this, from);
}
//
//int String::lastIndexOf(const RegExp &exp, int from) const
//{
//	return exp.lastIndexIn(this->c_str(), from);
//}
//

int String::count(const RegExp &exp) const
{
	return exp.captureCount(*this);
}


String String::mid(int position, int offset) const
{
	return substr(position, offset);
}

bool String::replace(const RegExp & rex, const String & fmt, Ct::CaseSensitivity cs)
{
	//remove constness
	auto &_rex = const_cast<RegExp&>(rex);
	//set CaseSensitivity flag
	_rex.setCaseSensitivity(cs);

	return  _rex.replace(*this, fmt);
}

bool String::replace(const String & oldVal, const String & newVal)
{
	auto _begin = begin();
	for (; _begin != end(); ++_begin) {
		int offset = std::distance(begin(), _begin); //were we are
		if (std::wstring::compare(offset, oldVal.length(), oldVal) == 0) 
			break;//we found it
	}
	//not found
	if (_begin != end()) return false;
	
	//erase former entries and insert new value(s)
	auto _itInsertPtr = insert(erase(_begin, std::next(_begin, oldVal.length())),newVal.begin(),newVal.end());
	
	if (_itInsertPtr == end()) return false;

	return true;
}

bool String::replace(const wchar_t oldVal, const wchar_t newVal, size_t offset)
{
	bool _found = false;
	for (auto _begin = std::next(begin(),offset); _begin != end(); ++_begin) 
		if (*_begin == oldVal) {
			*_begin = newVal;
			_found = true;
		}
	return _found;
}

String String::formatString(String s, ...)
{
	va_list _vArgList;
	va_start(_vArgList, s);
	String _result(size_t(1 + std::vswprintf(NULL, 0, s.c_str(), _vArgList)));
	std::vswprintf(const_cast<wchar_t*const>(_result.data()), _result.size(), s.c_str(), _vArgList);
	va_end(_vArgList);
	return _result;
}

void String::appendFormat(String fmt, ...)
{
	va_list _vlArg;
	va_start(_vlArg, fmt);
	append(formatString(fmt, _vlArg));
	va_end(_vlArg);
}

bool String::isequal(const String & right, Ct::CaseSensitivity cs)
{
	//self comparison true always
	if (this == &right) return true;
	switch (cs) {
	case Ct::CaseInsensitive:
		return (right.size() == size() && std::equal(begin(), end(), right.begin(), [&](auto _first, auto _second) {
			if (std::towlower(_first) != std::towlower(_second)) return false;
			return true;
		}));
		break;
	case Ct::CaseSensitive:
		return (right.size() == size() && std::equal(begin(), end(), right.begin(), std::equal_to<String::value_type>()));
		break;
	}
	return true;
}

int String::compare_l(const String & Input, const std::locale &loc)
{
	const std::collate<wchar>& coll = std::use_facet<std::collate<wchar> >(loc);
	auto _ptrFirst = Input.data();
	auto _ptrSecond = data();
	return coll.compare(_ptrFirst, _ptrFirst + Input.size(), _ptrSecond, _ptrSecond + size());
}

void String::trim(int offset)
{
	trim_right(*this);
	trim_left(*this,offset);
}

//Search string for substring. 
//Elements are compared case insensitively.
//\param Test A test sequence
//\param Loc A locale used for case insensitive comparison
//\return The result of the test
//
//\note This function provides the strong exception-safety guarantee
//*/

bool String::contains_l(const String & Test, const std::locale & Loc)
{
	auto& f = std::use_facet<std::collate<String::value_type>>(loc);
	auto _ItBegin = begin();
	for (; _ItBegin != end(); ++_ItBegin) {
		int offset = std::distance(begin(), _ItBegin);
		//messure to Test string
		auto _last1 = (c_str() + offset) + Test.length();
		//0 is equal
		if (f.compare(c_str() + offset, _last1, Test.c_str(),
			Test.c_str() + Test.length()) == 0) {
			return true;
		}
	}
	return false;
}
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

bool String::ends_with(const String & Input, const String & Test, const std::locale & loc)
{
	const_reverse_iterator InputEnd = Input.rend();
	const_reverse_iterator TestEnd = Test.rend();

	const_reverse_iterator it = Input.rbegin();
	const_reverse_iterator pit = Test.rbegin();

	for (;
		it != InputEnd && pit != TestEnd;
		++it, ++pit)
	{
		if (!(isequal_l(*it, *pit, loc)))
			return false;
	}

	return pit == TestEnd;
}

bool String::isequal_l(String::value_type input, String::value_type test, const std::locale & loc)
{
	auto &fset = std::use_facet<std::collate<String::value_type>>(loc);
	if (fset.compare(&input, &input + 1, &test, &test + 1) == 0)
		return true;

	return false;
}

/*
//This predicate holds when the test string is a prefix of the Input.
//In other words, if the input starts with the test.
//When the optional predicate is specified, it is used for character-wise
//comparison.
//
//\param Input An input sequence
//\param Test A test sequence
//\param Comp An element comparison predicate
//\return The result of the test
*/

bool String::starts_with(const String & Input, const String & Test, const std::locale & loc)
{
	const_iterator InputEnd = Input.end();
	const_iterator TestEnd = Test.end();

	const_iterator it = Input.begin();
	const_iterator pit = Test.begin();
	for (;
		it != InputEnd && pit != TestEnd;
		++it, ++pit)
	{
		if (!(isequal_l(*it, *pit, loc)))
			return false;
	}

	return pit == TestEnd;
}

inline String::iterator String::trim_begin(iterator InBegin, iterator InEnd)
{
	iterator It = InBegin;
	for (; It != InEnd; ++It)
		if (!IsSpace(*It))
			return It;
	return It;
}

inline String::iterator String::trim_end(iterator InBegin, iterator InEnd)
{
	int _len = std::distance(InBegin, InEnd) - 1;
	auto rIt = rbegin();
	auto It = begin();
	for (; rIt != rend(); ++rIt, --_len) {
		if (!IsSpace(*rIt)) {
			It = (begin() + _len);
			break;
		}
	}
	return It;
}
