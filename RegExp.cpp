#include <algorithm>
#include <iterator>
#include <regex>
#include "RegExp.h"
#include "CString.h"

#ifdef DEBUG
#include "Debug.h"
#endif // DEBUG

RegExp::RegExp(const String &s, PatternSyntax _Flag)
	: m_pattern(new String(s)), m_last_mat(0), m_patternSyntax(_Flag) 
{
	try 
	{
		m_wregex.assign(s, _Flag);
	}
	catch (std::regex_error &e)
	{
		m_invalidRegExpSyntax = true;
		debugl(String::formatString("RegExp Error: %d\n", e.code()));
		return;//leave here if we got exception
	}

	//if everything went well, here is false
	m_invalidRegExpSyntax = false;
}
RegExp::RegExp(const wchar *s, PatternSyntax _Flag)
	: m_pattern(new String(s)), m_last_mat(0), m_patternSyntax(_Flag) 
{
	try
	{
		m_wregex.assign(s, _Flag);
	}
	catch (std::regex_error &e)
	{
		m_invalidRegExpSyntax = true;
		debugl(String::formatString("RegExp Error: %d\n", e.code()));
		return;//leave here if we got exception
	}
	//if everything went well, here is false
	m_invalidRegExpSyntax = false;
}

RegExp::RegExp(const wchar *s, size_t _count, PatternSyntax _Flag)
	: m_pattern(new String(s)), m_last_mat(0), m_patternSyntax(_Flag) 
{
	try
	{
		m_wregex.assign(s,_count, _Flag);
	}
	catch (std::regex_error &e)
	{
		m_invalidRegExpSyntax = true;

		debugl(String::formatString("RegExp Error: %d\n", e.code()));
		return;//leave here if we got exception
	}

	//if everything went well, here is false
	m_invalidRegExpSyntax = false;
}

template<class _InIt>
RegExp::RegExp(_InIt beg, _InIt end, PatternSyntax _Flag)
	: m_pattern(new String()), m_last_mat(0), m_flag(_Flag)
{
	try
	{
		m_wregex.assign(beg, end, _Flag);
	}
	catch (std::regex_error &e)
	{
		m_invalidRegExpSyntax = true;

		debugl(String::formatString("RegExp Error: %d\n", e.code()));
		return;//leave here if we got exception
	}

	//if everything went well, here is false
	m_invalidRegExpSyntax = false;

	std::copy(beg, end, m_pattern.begin());
}

RegExp::RegExp(std::initializer_list<wchar> &list, PatternSyntax _Flag)
	: m_pattern(new String()), m_last_mat(0), m_patternSyntax(_Flag)
{
	try
	{
		m_wregex.assign(list, _Flag);
	}
	catch (std::regex_error &e)
	{
		m_invalidRegExpSyntax = true;

		debugl(String::formatString("RegExp Error: %d\n", e.code()));
		return;//leave here if we got exception
	}

	//if everything went well, here is false
	m_invalidRegExpSyntax = false;

	std::copy(list.begin(), list.end(), m_pattern->begin());
}
void RegExp::assign(const String &s, PatternSyntax _Flag)
{
	m_wregex = std::wregex(s, _Flag); m_pattern = new String(s); m_last_mat = 0;  m_patternSyntax = _Flag;
}
void RegExp::assign(const wchar *s, size_t _count, PatternSyntax _Flag)
{
	m_wregex = std::wregex(s, _count, _Flag); m_pattern = new String(s); m_last_mat = 0; m_patternSyntax = _Flag;
}
RegExp::~RegExp() { delete m_pattern; }

String RegExp::pattern() const
{
	return *m_pattern;
}

void RegExp::setPattern(const String & pattern) {
	*m_pattern = pattern;
}

Ct::CaseSensitivity RegExp::caseSensitivity() const
{
	return m_caseSensitive;
}

void RegExp::setCaseSensitivity(Ct::CaseSensitivity cs)
{
	switch (cs) {
	case Ct::CaseInsensitive:
		m_patternSyntax = icase | ECMAScript;
		m_wregex = std::wregex(pattern(), m_patternSyntax);
		break;
	case Ct::CaseSensitive:
		m_wregex = std::wregex(pattern(), ECMAScript);
		m_patternSyntax = ECMAScript;
		break;
	}
}

bool RegExp::exactMatch(const String & str) const
{
	return std::regex_match(str, m_wregex);
}
int RegExp::indexIn(const String & str, int offset) const
{
	return const_cast<RegExp*>(this)->indexIn(str, offset);
}
/*
Attempts to find a match in str from position offset (0 by default). If offset is -1,
the search starts at the last character; if -2, at the next to last character; etc.
*/
int RegExp::indexIn(const String & str, int offset)
{
	if (offset < 0 || offset > (int)str.length() || str.empty()) return -1;

	if (!m_pattern) return -1;

	//save last upset
	m_last_offset = offset;

	//capture sub-strings
	setCaptureList(str);

	begin_iter = std::wsregex_iterator(std::next(str.begin(), offset), str.end(), m_wregex);
	end_iter = std::wsregex_iterator();

	if (begin_iter == end_iter) return -1;

	return begin_iter->position(0) + offset;
}

//Returns the length of the last matched string, or -1 if there was no match.
int RegExp::matchedLength() const
{
	if (begin_iter == end_iter) return -1;

	return begin_iter->length(0);
}

int RegExp::lastMatchIn(const String &s, int offset) const
{
	if (offset < 0 || offset > (int)s.length() || s.empty()) return -1;

	if (!m_pattern) return -1;

	//capture sub-strings
	setCaptureList(s);

	size_t index = s.length() - std::distance(wsregex_rev_iterator(s.rbegin(), s.rend(), m_wregex),
		wsregex_rev_iterator());

	if (index < 0 || index > s.length()) return -1;
	return index;
}
bool RegExp::replace(String & s, const String &_rep, MatchType match_type) const
{
	auto _sResult = std::regex_replace(s, m_wregex, _rep, match_type);
	if (_sResult.length() <= 0 || _sResult.empty()) return false;
	s.assign(_sResult);
	return true;
}
RegExp::MatchCapturedVector RegExp::tokenize(const String &s, int offset, MatchType match_type) const
{
	MatchCapturedVector _mcvMatchCaptureVector;

	auto _mcvBeginIter = _mcvMatchCaptureVector.begin();
	auto _rtBeginIter = std::wsregex_token_iterator(s.begin(), s.end(), m_wregex, 0, match_type);
	for (; _rtBeginIter != std::wsregex_token_iterator(); ++_rtBeginIter) {
		_mcvMatchCaptureVector.push_back(MatchCaptured{(int)s.find(_rtBeginIter->str()),_rtBeginIter->str()});
	}
	return _mcvMatchCaptureVector;
}

//Returns the number of captures contained in the regular expression.
int RegExp::captureCount() const { return m_capturedStringList.size(); }

//Returns a list of the captured text strings.
StringList RegExp::capturedTexts() const
{
	if (m_capturedStringList.empty())
		return StringList();

	return m_capturedStringList;
}

//Returns a list of the captured text strings.
StringList RegExp::capturedTexts()
{
	if (m_capturedStringList.empty())
		return StringList();

	return m_capturedStringList;
}

StringList RegExp::captureTexts(const String & str, MatchType match_type)
{
	StringList _slCapturedStringList;
	auto _begin_iter = std::wsregex_iterator(str.begin(), str.end(),m_wregex);
	auto _end_iter = std::wsregex_iterator();

	while (_begin_iter != _end_iter) {
		_slCapturedStringList.push_back(_begin_iter->str());
		++_begin_iter;
	}
	return _slCapturedStringList;
}
int RegExp::captureCount(const String & str) const
{
	auto _begin_iter = std::wsregex_iterator(str.begin(), str.end(), m_wregex);
	auto _end_iter = std::wsregex_iterator();
	return std::distance(_begin_iter, _end_iter);
}
//Returns the text captured by the nth subexpression.
String RegExp::cap(int nth) const
{
	if (m_capturedStringList.empty())
		return String();

	return m_capturedStringList[nth];
}

//Returns the text captured by the nth subexpression.
String RegExp::cap(int nth)
{
	if (m_capturedStringList.empty())
		return String();

	return m_capturedStringList[nth];
}

int RegExp::pos(int nth) const
{
	if (m_capturedStringList.empty())
		return -1;

	return std::distance(m_capturedStringList.begin() + nth, m_capturedStringList.end());
}

int RegExp::pos(int nth)
{
	if (m_capturedStringList.empty())
		return -1;

	return std::distance(m_capturedStringList.begin() + nth, m_capturedStringList.end());
}

void RegExp::setCaptureList(const String &s, MatchType match_type) const
{
	//avoid repeation
	const_cast<StringList&>(m_capturedStringList).clear();

	typedef std::vector<std::wstring> _StringList;
	std::vector<std::wstring> _wstring_list;
	std::copy(std::wsregex_token_iterator(s.begin(), s.end(), m_wregex, 0, match_type),
		std::wsregex_token_iterator(), std::insert_iterator<_StringList>(_wstring_list, _wstring_list.begin()));
	insert_item(const_cast<StringList&>(m_capturedStringList), _wstring_list);
}

