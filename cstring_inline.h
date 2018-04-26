#include "cstring.h"
#ifndef CSTRING_INLINE_H
#define CSTRING_INLINE_H

inline void CString::push_back(char chSymbol)
{
	m_strCore.push_back(chSymbol);
}

inline CString& CString::operator = (std::string const& strString)
{
	m_strCore = strString;
	return *this;
}

inline CString& CString::operator = (char const& strChar)
{
	m_strCore = strChar;
	return *this;
}

inline char CString::operator[](unsigned nIndex)
{
	return m_strCore[nIndex];
}

inline CString CString::GetExtention() const
{
	return m_strCore.substr(m_strCore.find_last_of('.') + 1);
}

#endif