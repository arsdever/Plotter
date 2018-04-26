#include "cstring.h"

CString::CString()
{
}
CString::CString(const char *const strInit)
	: m_strCore(strInit)
{
}

CString::CString(char const& strInit)
{
	m_strCore = strInit;
}

CString::CString(std::string strInit)
	: m_strCore(strInit)
{
}

CString::~CString()
{
}

CString& CString::Arg(CString const& strArgument)
{
	int nArg = m_strCore.find_last_of("%");

	if (nArg < 0)
		return *this;

	CString strResult = m_strCore.substr(0, nArg);
	strResult += strArgument;
	strResult += m_strCore.substr(nArg + 1);
	m_strCore = strResult.m_strCore;

	return *this;
}

CString CString::Arg(CString const& strArgument) const
{
	CString str(m_strCore);
	int nArg = m_strCore.find_last_of("%");

	if (nArg < 0)
		return str;

	CString strResult = m_strCore.substr(0, nArg);
	strResult += strArgument;
	strResult += m_strCore.substr(nArg + 1);
	str.m_strCore = strResult.m_strCore;

	return str;
}

CString CString::ToLower() const
{
	std::string string = m_strCore;

	for (unsigned i = 0; i < string.length(); ++i)
	{
		if (string[i] >= 'A' && string[i] <= 'Z')
			string[i] += 'a' - 'A';
	}

	return string;
}

CString CString::ToUpper() const
{
	std::string string = m_strCore;

	for (unsigned i = 0; i < string.length(); ++i)
	{
		if (string[i] >= 'a' && string[i] <= 'z')
			string[i] += 'A' - 'a';
	}

	return string;
}

CStringList CString::Split(char chSymbol) const
{
	CStringList list;
	std::string str = m_strCore;
	int nIndex;

	while ((nIndex = str.find_last_of(chSymbol)) != std::string::npos)
	{
		list.push_front(str.substr(nIndex + 1));
		str[nIndex] = '\0';
		str.resize(nIndex);
	}
	list.push_front(str);

	return list;
}

CString& CString::operator += (CString const& strString)
{
	m_strCore += strString.m_strCore;

	return *this;
}

CString::operator std::string()
{
	return m_strCore;
}

std::istream& operator >> (std::istream &stream, CString string)
{
	return stream >> string.m_strCore;
}

std::ostream& operator << (std::ostream &stream, CString const& string)
{
	return stream << string.m_strCore;
}

CString operator + (CString const& strString1, CString const& strString2)
{
	return strString1.m_strCore + strString2.m_strCore;
}

CString operator + (CString const& strString1, std::string const& strString2)
{
	return strString1.m_strCore + strString2;
}

CString operator + (std::string const& strString1, CString const& strString2)
{
	return strString1 + strString2.m_strCore;
}

CString operator + (char const& strString1, CString const& strString2)
{
	return CString(strString1) + strString2;
}

CString operator + (CString const& strString1, char const& strString2)
{
	return strString1.m_strCore + CString(strString2);
}
