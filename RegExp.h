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
#ifndef CT_REG_EXP_H
#define CT_REG_EXP_H

#include <regex>
#include <vector>
#include "global.h"
#include "CString.h"
#include "utilitydef.h"
#include "compilerdefines.h"

CT_DECLARE_FLAGS(PatternSyntax, std::wregex::flag_type)
CT_DECLARE_FLAGS(MatchType, std::regex_constants::match_flag_type)

class RegExp 
{
public:
	struct MatchCaptured {
		int position;
		std::wstring str;
	};
	typedef typename std::iterator<std::input_iterator_tag, wchar_t> iterator;
	typedef std::regex_iterator<std::wstring::const_reverse_iterator> wsregex_rev_iterator;
	typedef std::vector<MatchCaptured> MatchCapturedVector;
	typedef std::basic_regex<wchar>	RegExpType;
	typedef wchar_t wchar;
	typedef std::regex_constants::syntax_option_type regex_constants;
	typedef regex_constants flag_type;

	static constexpr flag_type icase = regex_constants::icase;
	static constexpr flag_type nosubs = regex_constants::nosubs;
	static constexpr flag_type optimize = regex_constants::optimize;
	static constexpr flag_type collate = regex_constants::collate;
	static constexpr flag_type ECMAScript = regex_constants::ECMAScript;
	static constexpr flag_type basic = regex_constants::basic;
	static constexpr flag_type extended = regex_constants::extended;
	static constexpr flag_type awk = regex_constants::awk;
	static constexpr flag_type grep = regex_constants::grep;
	static constexpr flag_type egrep = regex_constants::egrep;

	
	RegExp() : m_last_mat(0) {}
	~RegExp();

	RegExp(const String &s, PatternSyntax _Flag = RegExp::ECMAScript);

	RegExp(const wchar *s, PatternSyntax _Flag = RegExp::ECMAScript);

	RegExp(const wchar *s, size_t _count, PatternSyntax _Flag = RegExp::ECMAScript);

	template<class _InIt> RegExp(_InIt beg, _InIt end, PatternSyntax _Flag = RegExp::ECMAScript);

	RegExp(std::initializer_list<wchar>&, PatternSyntax _Flag = RegExp::ECMAScript);

	void assign(const String & s, PatternSyntax _Flag);

	void assign(const wchar * s, size_t _count, PatternSyntax _Flag);

	operator RegExpType() { return m_wregex; }

	RegExp & RegExp::operator=(RegExp && other)
	{
		//assignment to self is not a valid operation so return
		if (this == &other) return *this;

		//use the parent assignment operator instead
		assign(other.pattern(), other.patternSyntax());

		return *this;
	}

	bool RegExp::operator==(const RegExp & rx) const
	{
		if (this == &rx && pattern() == rx.pattern()) return true;
		return false;
	}

	bool isEmpty() const { return m_wregex._Empty(); }
	bool isValid() const {}


	String pattern() const;
	void setPattern(const String &pattern);

	Ct::CaseSensitivity caseSensitivity() const;
	void setCaseSensitivity(Ct::CaseSensitivity cs);

	PatternSyntax patternSyntax() const { return m_patternSyntax; };
	void setPatternSyntax(PatternSyntax syntax) { m_patternSyntax = syntax; };

	bool exactMatch(const String &str) const;
	int indexIn(const String &str, int offset = 0) const;

	StringList captureTexts(const String &str, MatchType match_type = MatchType::enum_type::match_default);

	int captureCount(const String & str) const;

	/*last match substring in a string*/
	int lastMatchIn(const String & s, int offset = 0) const;

	bool replace(String & s, const String& _rep, MatchType match_type = MatchType::enum_type::match_default) const;

	RegExp::MatchCapturedVector tokenize(const String & s, int offset = 0,
		MatchType match_type = std::regex_constants::match_default) const;

	int matchedLength() const;

#ifndef NO_REGEXP_CAPTURE
	int captureCount() const;;

	StringList capturedTexts() const;
	StringList capturedTexts();

	String cap(int nth = 0) const;
	String cap(int nth = 0);

	int pos(int nth = 0) const;
	int pos(int nth = 0);
#endif
private:
	//in case of no constnest 
	int indexIn(const String &str, int offset = 0);

	PatternSyntax m_patternSyntax;

	void setCaptureList(const String &s, MatchType match_type = MatchType::enum_type::match_default)const;
	int m_last_mat, m_last_offset;
	String  *m_pattern, *m_pArgString;
	StringList m_capturedStringList;
	Ct::CaseSensitivity m_caseSensitive;
	mutable int m_matchPos;
	std::wsregex_iterator begin_iter;
	std::wsregex_iterator end_iter;

	RegExpType  m_wregex;

	bool m_invalidRegExpSyntax;
};


#endif // !CT_REG_EXP_H


