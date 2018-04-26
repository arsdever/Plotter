#ifndef CEXCEPTION_H
#define CEXCEPTION_H

#ifndef REDIR_EXCEPTION
#define REDIR_EXCEPTION(RUNBLOCK)								\
		try														\
		{														\
			##RUNBLOCK											\
		}														\
		catch (CException &err)									\
		{														\
			err.FromPath(EXCEPT_PATH);							\
			throw err;											\
		}									
#define REDIR_EXCEPTION_EXTRA(RUNBLOCK,CLEARBLOCK)				\
		try														\
		{														\
			##RUNBLOCK											\
		}														\
		catch (CException &err)									\
		{														\
			##CLEARBLOCK										\
			err.FromPath(EXCEPT_PATH);							\
			throw err;											\
		}										
#endif

#include "cstring.h"
#include <list>

extern const CString NoGraphSelected;
extern const CString InvalidCommand;
extern const CString FewArguments;
extern const CString UnknownArgument;
extern const CString NameAlreadyExist;

class CException {
public:
	enum EErrorType {
		Critical,
		Warning,
		Message
	};

public:
	// Constructor
	CException(CString const& strMessage = "Unknown error", CString const& strPath = "", EErrorType eType = Critical)
		: m_strMessage(strMessage)
		, m_eType(eType)
	{
		m_lExceptionPath.push_front(strPath);
	}
	virtual ~CException() = default;

    // Add handler to path
    virtual inline void FromPath(CString const& strPath) { m_lExceptionPath.push_front(strPath); }
    // Get error path
    virtual inline CString GetPath() const;
    // Get error message
    virtual inline CString const& What() const { return m_strMessage; }
	// Get error type
	virtual inline EErrorType GetType() const { return m_eType; }

private:
	CString m_strMessage;
    std::list<CString> m_lExceptionPath;
	EErrorType m_eType;
};

inline CString CException::GetPath() const
{
    std::string strPath;
    for(auto it : m_lExceptionPath)
    {
        strPath += '\t' + it + '\n';
    }

	return strPath;
}

class CError : public CException
{
public:
	CError(CString const& strMessage = "Unknown error", CString const& strPath = "")
		: CException(strMessage, strPath, Critical)
	{}
};

class CWarning : public CException
{
public:
	CWarning(CString const& strMessage = "Unknown warning", CString const& strPath = "")
		: CException(strMessage, strPath, Warning)
	{}
};

class CMessage : public CException
{
public:
	CMessage(CString const& strMessage = "Unknown message", CString const& strPath = "")
		: CException(strMessage, strPath, Message)
	{}
};

#endif